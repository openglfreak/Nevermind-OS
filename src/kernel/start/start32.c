#include "../protected_mode/tss.h"
#include "../../memconsts/memconsts.h"

#define MEMCPY(s,d,l) __asm__ ("cld\nrep movsb\n" : : "+S" (s), "+D" (d), "+c" (l))
#define DIV0() __asm__ __volatile__ ("div %%ecx\n" : : "a" (1), "c" (0), "d" (0))

extern void register_interrupts();
extern void initialize_memory_manager();
extern uint32_t allocate_physical_page(uint32_t);

void start32();
void jmp_ring(uint16_t cs, uint16_t ds, uint16_t ss, uint32_t esp, uint32_t eip, uint8_t ring);
void get_cpuid_feature_info();
void enable_paging();
void identity_map(uint32_t, uint32_t, uint32_t);
void setup_usermode_segments();

GDT_ENTRY* const zero = &gdt->entries[0];
GDT_ENTRY* const kernel_code = &gdt->entries[1];
GDT_ENTRY* const kernel_data = &gdt->entries[2];
GDT_ENTRY* const user_code = &gdt->entries[3];
GDT_ENTRY* const user_data = &gdt->entries[4];
GDT_ENTRY* const user_tss = &gdt->entries[5];

GDTR gdtr;
TSS tss;

PAGE_TABLE user_ptable;

void user()
{
}

void __attribute__ ((used, noreturn)) start32()
{
    register_interrupts();
    get_cpuid_feature_info();
    enable_paging();
    initialize_memory_manager();
    setup_usermode_segments();
    jmp_ring(0x18, 0x20, 0x20, 0x1000, (uint32_t)&user, 0x03);
    while (1)
        __asm__ __volatile__ ("cli\nhlt\n");
}

void jmp_ring(uint16_t cs, uint16_t ds, uint16_t ss, uint32_t esp, uint32_t eip, uint8_t ring)
{
    __asm__ __volatile__ ("movl 0x0C(%%esp),%%eax\nmovw %w2,%%ds\nmov %%eax,(%3)\nmovw %w1,%%ds\nmovw %w1,%%es\nmovw %w1,%%fs\nmovw %w1,%%gs\npushw %w2\npushl %3\npushfl\npushl %0\npushl %4\niretl\n" : : "ri" (cs | ring), "r" (ds | ring), "r" (ss | ring), "ri" (esp), "ri" (eip) : "%eax");
}

void get_cpuid_feature_info()
{
    __asm__ __volatile__ ("cpuid\n" : "=a" (*cpuid_signature), "=d" (*cpuid_features0), "=c" (*cpuid_features1), "=b" (*cpuid_additional_features) : "0" (1));
    *cpuid_features0 &= ~0x08;
}

void enable_paging()
{
    uint32_t i = 1024;
    while (--i > 0)
        pdir->entries[i] = 0;
    identity_map(0, *cpuid_features0 & 0x08 ? 0 : (uint32_t)ptable0_start, PAGE_TABLE(0x00,0,0,0,0,1,0,1,1));
    LOAD_PAGE_DIRECTORY(pdir_start);
    if (*cpuid_features0 & 0x08)
        ENABLE_PAGING_PSE();
    else
        ENABLE_PAGING();
}

void identity_map_autosize(uint32_t pdir_entry, uint32_t ptable_start, uint32_t attributes)
{
    identity_map(pdir_entry, *cpuid_features0 & 0x08 ? 0 : (uint32_t)ptable_start, attributes);
}

void identity_map(uint32_t pdir_entry, uint32_t ptable_start, uint32_t attributes)
{
    if (ptable_start == 0)
        pdir->entries[pdir_entry] = PAGE_DIRECTORY_ADDRESS(pdir_entry << 22) | PAGE_DIRECTORY_SIZE_4MB | attributes;
    else
    {
        pdir->entries[pdir_entry] = PAGE_DIRECTORY_ADDRESS(ptable_start) | (attributes & (PAGE_DIRECTORY_SIZE_4MB - 1));
        uint16_t i = 1024;
        uint32_t o = pdir_entry << 22;
        while (i--)
            ((PAGE_TABLE*)ptable_start)->entries[i] = PAGE_TABLE_ADDRESS(o + (i << 12)) | (attributes & (PAGE_TABLE_ADDRESS(1) - 1));
    }
}

void setup_usermode_segments()
{
    tss.ss0 = 0x10;
    tss.esp0 = stack_end;
    GDT_ENTRY g;
    g.limit_low = 0xFFFF;
    g.base_low = 0x0000;
    g.base_middle = 0x00;
    g.access = GDT_ACCESS(1,3,1,0,1,0);
    g.limit_high_and_flags = GDT_LIMIT_FLAGS(1,1,0,0x0F);
    g.base_high = 0x00;
    gdt->entries[3] = g;
    g.limit_low = 0xFBFF;
    g.base_middle = 0x40;
    g.access = GDT_ACCESS(1,3,0,0,1,0);
    gdt->entries[4] = g;
    g = GDT_TSS_ENTRY(&tss,3);
    gdt->entries[5] = g;
    gdtr.limit = 0x30;
    gdtr.base = (uint32_t)gdt_start;
    identity_map(1, *cpuid_features0 & 0x08 ? 0 : (uint32_t)&user_ptable, PAGE_TABLE(0x00,0,0,0,0,1,1,1,1));
    INVALIDATE_ALL_PAGES();
    __asm__ __volatile__ ("lgdtw (%0)\n" : : "r" (&gdtr));
    __asm__ __volatile__ ("ltrw %w0\n" : : "r" (0x28));
}
