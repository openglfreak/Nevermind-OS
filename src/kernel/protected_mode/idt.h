#ifndef _IDT
#define _IDT

#include <stdint.h>

#define IDT_ATTR_PRESENT 0x80
#define IDT_ATTR_MIN_DESCRIPTOR_PRIVILEGE(r) (((r)&0x03)<<0x05)
#define IDT_ATTR_STORAGE 0x10
#define IDT_TYPE_TRAP_32BIT 0x0F
#define IDT_TYPE_INTERRUPT_32BIT 0x0E
#define IDT_TYPE_TRAP_16BIT 0x07
#define IDT_TYPE_INTERRUPT_16BIT 0x06
#define IDT_TYPE_TASK_32BIT 0x05
#define IDT_TYPE_AND_ATTRIBUTES(p,dpl,s,t) \
        (((p)?IDT_ATTR_PRESENT:0x00) |\
        IDT_ATTR_MIN_DESCRIPTOR_PRIVILEGE(dpl) |\
        ((s)?IDT_ATTR_STORAGE:0x00) |\
        ((t)&0x07)

typedef struct __attribute__((packed)) {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_and_attributes;
    uint16_t offset_high;
} IDT_GATE;

typedef struct __attribute__((packed)) {
    IDT_GATE gates[256];
} IDT;

typedef struct __attribute__((packed)) {
    uint16_t limit;
    uint32_t base;
} IDTR;

#endif // _IDT
