#include <stdint.h>
#include "../../memconsts/memconsts.h"

void start32();
int32_t ltoa(int64_t, int, int, int8_t*);
int32_t printint64_t(int64_t, int, int);
int32_t printhex(int64_t, int);

void __attribute__ ((used, noreturn)) start32()
{
    int32_t i = 0x1000;
    int8_t* p = (int8_t*)0xB9000;
    while (i-- > 0)
    {
        *p-- = 0;
        *p-- = 0x0F;
    }
    i = printhex(memmap->entries[0].base, 0) + 1;
    i += printhex(0xEFFFFFFFFFFFFFFF, i) + 1;
    i += printhex(memmap->entries[0].limit, i) + 1;
    int32_t n = 1;
    for (; n < 20 || memmap->entries[n].limit; n++)
    {
        i += printhex(memmap->entries[n].base, i) + 1;
        i += printhex(memmap->entries[n].limit, i) + 1;
    }
    while (1)
        asm volatile ("cli\nhlt\n");
}

const int8_t digits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

int32_t ltoa(int64_t l, int32_t base, int32_t offset, int8_t* dest)
{
    int8_t buffer[64];
    int8_t* p = buffer;
    int32_t n = l < 0;
    if (n)
        l = -l;
    do
    {
        *p++ = digits[l % base];
        l /= base;
    }
    while (l != 0);
    if (n)
        *p++ = '-';
    n = p - buffer;
    l = n;
    p = buffer;
    dest[offset + l] = 0;
    while (l--)
        dest[offset + l] = *p++;
    return n;
}

int32_t printint64_t(int64_t l, int32_t base, int32_t start)
{
    int8_t buffer[32];
    l = ltoa(l, base, 0, buffer);
    int32_t n = (int)l;
    int8_t* d = (int8_t*)(0xB8000 + start * 2);
    while (l--)
        d[l * 2] = buffer[l];
    return n;
}

int32_t printhex(int64_t l, int32_t start)
{
    int8_t* d = (int8_t*)(0xB8000);
    d[start++ * 2] = '0';
    d[start++ * 2] = 'x';
    return printint64_t(l, 16, start) + 2;
}
