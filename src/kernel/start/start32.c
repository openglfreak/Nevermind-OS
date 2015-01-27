#include <stdint.h>
#include "../../memconsts/memconsts.h"

extern void initialize_memory_manager();

void start32();
void get_cpuid_feature_info();
void enable_paging();
void identity_map(uint32_t, uint32_t);

void __attribute__ ((used, noreturn)) start32()
{
    get_cpuid_feature_info();
    enable_paging();
    initialize_memory_manager();
    while (1)
        __asm__ __volatile__ ("cli\nhlt\n");
}

void get_cpuid_feature_info()
{
    __asm__ __volatile__ ("cpuid\n" : "=a" (*cpuid_signature), "=d" (*cpuid_features0), "=c" (*cpuid_features1) : "0" (1));
}

void enable_paging()
{
    uint32_t i = 1024;
    while (--i > 0)
        pdir->entries[i] = 0;
    identity_map(0, *cpuid_features0 & 0x08 ? 0 : (uint32_t)ptable0_start);
    LOAD_PAGE_DIRECTORY(pdir_start);
    ENABLE_PAGING_PSE();
}

void identity_map(uint32_t pdir_entry, uint32_t ptable_start)
{
    if (ptable_start == 0)
        pdir->entries[pdir_entry] = PAGE_DIRECTORY(pdir_entry * 0x400000,1,0,0,1,0,1,1);
    else
    {
        pdir->entries[pdir_entry] = PAGE_DIRECTORY(ptable_start,0,0,0,1,0,1,1);
        uint16_t i = 1024;
        uint32_t o = pdir_entry * 0x400000;
        while (i-- > 0)
            ptable0->entries[i] = PAGE_TABLE(o + i * 0x1000,0,0,0,0,1,0,1,1);
    }
}
