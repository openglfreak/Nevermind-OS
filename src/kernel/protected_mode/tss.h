#ifndef _TSS
#define _TSS

#define GDT_TSS_ENTRY(addr,privl) ((GDT_ENTRY){\
            .limit_low = 0x68,\
            .base_low = ((uint32_t)(addr)) & 0xFFFF,\
            .base_middle = (((uint32_t)(addr)) >> 16) & 0xFF,\
            .access = 0x89 | GDT_ACC_PRIVILEGE(privl),\
            .limit_high_and_flags = 0x40,\
            .base_high = ((uint32_t)(addr)) >> 24\
        })

typedef struct __attribute__ ((packed)) {
    uint32_t link;
    uint32_t esp0;
    uint32_t ss0;
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;
    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t fs;
    uint32_t gs;
    uint32_t ldt;
    uint16_t reserved;
    uint16_t iobp;
} TSS;

#endif // _TSS
