#include "../protected_mode/idt.h"
#include "../protected_mode/tss.h"
#include "../../memconsts/memconsts.h"

typedef struct __attribute__ ((packed)) {
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t esp;
    uint16_t ss;
} IRET_INFO;

extern void remap_pic(uint8_t, uint8_t);
extern void (*isr_table)();
extern void (*isr_table_end)();
extern uint8_t isr_attribute_table[];

IDTR idtr;

void __attribute__ ((used)) register_interrupts()
{
    remap_pic(0x20,0x28);
    
    uint32_t i = 0;
    for (; i < 256; i++)
    {
        uint32_t address = ((uint32_t)&isr_table) + (i << 3);
        idt->gates[i].offset_low = (uint16_t)address;
        idt->gates[i].selector = 0x08;
        idt->gates[i].zero = 0x00;
        idt->gates[i].type_and___attribute__s = isr_attribute_table[i];
        idt->gates[i].offset_high = (uint16_t)(address >> 16);
    }
    idtr.limit = (uint32_t)isr_table_end - (uint32_t)isr_table;
    idtr.base = (uint32_t)idt_start;
    __asm__ __volatile__ ("lidtw (%0)\n" : : "r" (&idtr));
}

uint32_t handle_exception(uint32_t* eflags, uint32_t* error_code, uint8_t* stack, uint8_t exception_number)
{
    return 0;
}

uint32_t handle_irq(uint32_t* eflags, uint32_t* error_code, IRET_INFO* iret_info, uint8_t irq_number)
{
    return 0;
}

uint32_t handle_interrupt(uint32_t* eflags, uint32_t* error_code, IRET_INFO* iret_info, uint8_t interrupt_number)
{
    return 0;
}

uint32_t isr_handler(uint32_t* eflags, uint32_t* error_code, uint8_t* stack, uint8_t interrupt_number)
{
    uint32_t ret = 0;
    if (interrupt_number == 39 || interrupt_number == 47)
    {
        PIC_READ_ISR(interrupt_number == 39,&ret);
        if ((ret & 0x80) != 0)
        {
            if (interrupt_number == 47)
                PIC_SEND_EOI_MASTER();
            return 0;
        }
        ret = 0;
    }
    else if (interrupt_number == 8 || (interrupt_number >= 10 && interrupt_number <= 14) || interrupt_number == 17 || interrupt_number == 30)
        ret = 4;
    if (interrupt_number > 32)
    {
        if (interrupt_number > 47)
            return ret + handle_interrupt(eflags, error_code, (IRET_INFO*)stack, interrupt_number);
        ret += handle_irq(eflags, error_code, (IRET_INFO*)stack, interrupt_number - 32);
        if (interrupt_number > 40)
            PIC_SEND_EOI_SLAVE();
        PIC_SEND_EOI_MASTER();
        return ret;
    }
    return ret + handle_exception(eflags, error_code, stack, interrupt_number);
}

uint32_t __attribute__ ((used)) isr_handler_wrapper(uint32_t eflags, uint32_t error_code, uint32_t stack, uint32_t interrupt_number)
{
    return isr_handler((uint32_t*)eflags, (uint32_t*)error_code, (uint8_t*)(stack + 0x04), (uint8_t)((interrupt_number - (uint32_t)&isr_table) / 0x08));
}
