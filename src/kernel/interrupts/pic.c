#include <stdint.h>
#include "pic.h"

#define INB(p,d) __asm__ __volatile__ ("inb %1,%%al\nmovzx %%al,%%eax\n" : "=a" (d) : "di" (p))
#define OUTB(p,b) __asm__ __volatile__ ("outb %%al,%0\n" : : "i" (p), "a" (b))
#define IOWAIT() __asm__ __volatile__ ("outb %%al,$0x80" : : "a" (0))

void remap_pic(uint8_t base_master, uint8_t base_slave)
{
    uint8_t mask_master;
    uint8_t mask_slave;
    INB(PIC_MASTER_DATA,mask_master);
    INB(PIC_SLAVE_DATA,mask_slave);
    
    OUTB(PIC_MASTER_COMMAND,ICW1(0,0,0,0,0,1));
    IOWAIT();
    OUTB(PIC_SLAVE_COMMAND,ICW1(0,0,0,0,0,1));
    IOWAIT();
    OUTB(PIC_MASTER_DATA,ICW2(base_master));
    IOWAIT();
    OUTB(PIC_SLAVE_DATA,ICW2(base_slave));
    IOWAIT();
    OUTB(PIC_MASTER_DATA,ICW3_MASTER_CASCADE_INTERRUPT(2));
    IOWAIT();
    OUTB(PIC_SLAVE_DATA,ICW3_SLAVE_CASCADE_INTERRUPT(2));
    IOWAIT();
    OUTB(PIC_MASTER_DATA,ICW4(0,0,0,1));
    IOWAIT();
    OUTB(PIC_SLAVE_DATA,ICW4(0,0,0,1));
    IOWAIT();
    
    OUTB(PIC_MASTER_DATA,mask_master);
    OUTB(PIC_SLAVE_DATA,mask_slave);
}
