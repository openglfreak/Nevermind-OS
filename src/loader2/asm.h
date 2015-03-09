#define CODE16() asm (".code16gcc\n")
#define CODE32() asm (".code32gcc\n")

#define LABEL(n) asm volatile (#n":\n")
#define JUMP_C(p) asm volatile ("jmp %0\n" : : "i" (p))
#define JUMP_L(n) asm volatile ("jmp "#n"\n")
#define JUMP_VN_W(p) asm volatile ("pushw %0\nretw\n" : : "g" (p))
#define JUMP_VN_L(p) asm volatile ("pushl %0\nretl\n" : : "g" (p))

#define MOVE_REG_VAR(r,v) asm volatile ("mov %%"#r",%0\n" : "=g" (v))
#define MOVE_VAR_REG(v,r) asm volatile ("mov %0,%%"#r"\n" : : "g" (v))

#define INTERRUPT(n) asm volatile ("int %0\n" : : "i" (n))
