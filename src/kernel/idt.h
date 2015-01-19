#ifndef IDT
#define IDT

#define IDT_ATTR_PRESENT 0x80
#define IDT_ATTR_MIN_DESCRIPTOR_PRIVILEGE(r) (((r)&0x03)<<0x05)
#define IDT_ATTR_STORAGE 0x10
#define IDT_TYPE_TASK_32BIT 0x05
#define IDT_TYPE_INTERRUPT_16BIT 0x06
#define IDT_TYPE_TRAP_16BIT 0x07
#define IDT_TYPE_INTERRUPT_32BIT 0x0E
#define IDT_TYPE_TRAP_32BIT 0x0F
#define IDT_TYPE_AND_ATTRIBUTES(p,dpl,s,t) \
        (((p)?IDT_ATTR_PRESENT:0x00) |\
        IDT_ATTR_MIN_DESCRIPTOR_PRIVILEGE(dpl) |\
        ((s)?IDT_ATTR_STORAGE:0x00) |\
        (t)

typedef struct __attribute__((packed)) {
    unsigned short offset_low;
    unsigned short selector;
    unsigned char zero;
    unsigned char type_and_attributes;
    unsigned short offset_high;
} IDT_GATE;

typedef struct __attribute__((packed)) {
    unsigned short limit;
    unsigned int base;
} IDTR;

#endif // IDT
