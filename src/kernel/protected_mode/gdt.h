#ifndef _GDT
#define _GDT

#define GDT_ACC_PRESENT 0x80
#define GDT_ACC_PRIVILEGE(r) (((r)&0x03)<<0x05)
#define GDT_ACC_ALWAYS_1 0x10
#define GDT_ACC_EXECUTABLE 0x08
#define GDT_ACC_DATA 0x00
#define GDT_ACC_DIRECTION_UP 0x00
#define GDT_ACC_DIRECTION_DOWN 0x04
#define GDT_ACC_CODE_READABLE 0x02
#define GDT_ACC_DATA_WRITABLE 0x02
#define GDT_ACC_READABLE_WRITABLE 0x02
#define GDT_ACC_ACCESSED 0x01
#define GDT_ACCESS(pr,privl,ex,dc,rw,ac) \
        (((pr)?GDT_ACC_PRESENT:0x00) |\
        GDT_ACC_PRIVILEGE(privl) |\
        GDT_ACC_ALWAYS_1 |\
        ((ex)?GDT_ACC_EXECUTABLE:GDT_ACC_DATA) |\
        ((dc)?GDT_ACC_DIRECTION_DOWN:GDT_ACC_DIRECTION_UP) |\
        ((rw)?GDT_ACC_READABLE_WRITABLE:0x00) |\
        ((ac)?GDT_ACC_ACCESSED:0x00))

#define GDT_FLAG_GRANULARITY_BYTE 0x00
#define GDT_FLAG_GRANULARITY_PAGE 0x08
#define GDT_FLAG_16BIT 0x00
#define GDT_FLAG_32BIT 0x04
#define GDT_FLAG_LONGMODE 0x02
#define GDT_FLAGS(gr,sz,l) \
        (((gr)?GDT_FLAG_GRANULARITY_PAGE:GDT_FLAG_GRANULARITY_BYTE) |\
        ((sz)?GDT_FLAG_32BIT:GDT_FLAG_16BIT) |\
        ((l)?GDT_FLAG_LONGMODE:0x00))

#define GDT_LIMIT_FLAGS(gr,sz,lm,limh) ((GDT_FLAGS(gr,sz,lm) << 4) | (limh & 0x0F))

typedef struct __attribute__((packed)) {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t limit_high_and_flags;
    uint8_t base_high;
} GDT_ENTRY;

typedef struct {
    GDT_ENTRY entries[1024];
} GDT;

typedef struct __attribute__((packed)) {
    uint16_t limit;
    uint32_t base;
} GDTR;

#endif // _GDT

