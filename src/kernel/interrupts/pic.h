#ifndef PIC
#define PIC

#define PIC_MASTER_BASE 0x20
#define PIC_MASTER_COMMAND PIC_MASTER_BASE
#define PIC_MASTER_DATA (PIC_MASTER_BASE+1)

#define PIC_SLAVE_BASE 0xA0
#define PIC_SLAVE_COMMAND PIC_SLAVE_BASE
#define PIC_SLAVE_DATA (PIC_SLAVE_BASE+1)

#define ICW1_ADDRESS(a) (((uint8_t)(a))&0xE0)
#define ICW1_INITIALIZE 0x10
#define ICW1_LEVEL_TRIGGERED 0x08
#define ICW1_EDGE_TRIGGERED 0x00
#define ICW1_INTERVALL_4 0x04
#define ICW1_INTERVALL_8 0x00
#define ICW1_SINGLE_MODE 0x02
#define ICW1_CASCADED_MODE 0x00
#define ICW1_ICW4 0x01
#define ICW1_NO_ICW4 0x00
#define ICW1(addr,l,i,s,c,icw4) \
        (ICW1_ADDRESS(addr) |\
        ICW1_INITIALIZE |\
        ((l)?ICW1_LEVEL_TRIGGERED:ICW1_EDGE_TRIGGERED) |\
        ((i)?ICW1_INTERVALL_4:ICW1_INTERVALL_8) |\
        ((s)?ICW1_SINGLE_MODE:ICW1_CASCADED_MODE) |\
        ((icw4)?ICW1_ICW4:ICW1_NO_ICW4))

#define ICW2_ADDRESS(a) a
#define ICW2(addr) ICW2_ADDRESS(addr)

#define ICW3_MASTER_CASCADE_INTERRUPT(i) (1<<(i))
#define ICW3_SLAVE_CASCADE_INTERRUPT(i) ((i)&0x07)

#define ICW4_SFNM 0x08
#define ICW4_FNM 0x00
#define ICW4_MASTER 0x04
#define ICW4_SLAVE 0x00
#define ICW4_AUTO_EOI 0x02
#define ICW4_8086 0x01
#define ICW4(s,m,a,m8086) \
        (((s)?ICW4_SFNM:ICW4_FNM) |\
        ((m)?ICW4_MASTER:ICW4_SLAVE) |\
        ((a)?ICW4_AUTO_EOI:0x00) |\
        ((m8086)?ICW4_8086:0x00))

#define PIC_EOI 0x20
#define PIC_ISR 0x0B
#define PIC_IRR 0x0A

#define PIC_SEND_COMMAND(m,c) __asm__ __volatile__ ("movw %w0,%%dx\nmovb %b1,%%al\noutb %%al,%%dx" : : "g" ((m)?PIC_MASTER_COMMAND:PIC_SLAVE_COMMAND), "g" (c) : "%al", "%dx")
#define PIC_SEND_DATA(m,c) __asm__ __volatile__ ("movw %w0,%%dx\nmovb %b1,%%al\noutb %%al,%%dx" : : "g" ((m)?PIC_MASTER_DATA:PIC_SLAVE_DATA), "g" (c) : "%al", "%dx")

#define PIC_READ_COMMAND(m,d) __asm__ __volatile__ ("movw %w0,%%dx\ninb %%dx,%%al" : : "g" ((m)?PIC_MASTER_COMMAND:PIC_SLAVE_COMMAND), "a" (*d) : "%dx")
#define PIC_READ_DATA(m,d) __asm__ __volatile__ ("movw %w0,%%dx\ninb %%dx,%%al" : : "g" ((m)?PIC_MASTER_DATA:PIC_SLAVE_DATA), "a" (*d) : "%dx")

#define PIC_SEND_EOI(m) PIC_SEND_COMMAND(m,PIC_EOI)
#define PIC_SEND_EOI_MASTER() PIC_SEND_EOI(1)
#define PIC_SEND_EOI_SLAVE() PIC_SEND_EOI(0)
#define PIC_SEND_EOI_BOTH() do {\
            PIC_SEND_EOI(0);\
            PIC_SEND_EOI(1);\
        } while (0)

#define PIC_READ_ISR(m,d) do {\
            PIC_SEND_COMMAND(m,PIC_ISR);\
            PIC_READ_COMMAND(m,d);\
        } while (0)
#define PIC_READ_ISR_MASTER(d) PIC_READ_ISR(1,d)
#define PIC_READ_ISR_SLAVE(d) PIC_READ_ISR(0,d)
#define PIC_READ_ISR_BOTH(md,sd) do {\
            PIC_READ_ISR(0,md);\
            PIC_READ_ISR(1,sd);\
        } while (0)

#define PIC_READ_IRR(m,d) do {\
            PIC_SEND_COMMAND(m,PIC_IRR);\
            PIC_READ_COMMAND(m,d);\
        } while (0)
#define PIC_READ_IRR_MASTER(d) PIC_READ_IRR(1,d)
#define PIC_READ_IRR_SLAVE(d) PIC_READ_IRR(0,d)
#define PIC_READ_IRR_BOTH(md,sd) do {\
            PIC_READ_IRR(0,md);\
            PIC_READ_IRR(1,sd);\
        } while (0)

#define PIC_SEND_MASK(m,mask) PIC_SEND_DATA(m,mask)
#define PIC_SEND_MASK_MASTER(mask) PIC_SEND_MASK(1,mask)
#define PIC_SEND_MASK_SLAVE(mask) PIC_SEND_MASK(0,mask)
#define PIC_SEND_MASK_BOTH(mmask,smask) do {\
            PIC_SEND_MASK(0,mmask);\
            PIC_SEND_MASK(1,smask);\
        } while (0)

#define PIC_SEND_DISABLE(m) PIC_SEND_MASK(m,0xFF)
#define PIC_SEND_DISABLE_MASTER() PIC_SEND_DISABLE(1)
#define PIC_SEND_DISABLE_SLAVE() PIC_SEND_DISABLE(0)
#define PIC_SEND_DISABLE_BOTH() PIC_SEND_MASK_BOTH(0xFF,0xFF)

#endif // PIC
