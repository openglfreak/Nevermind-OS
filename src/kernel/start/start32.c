void start32();
void delayloop();
void clearscreen();
int strlen(const char*);
void printcentered(int, const char*);

void start32()
{
    clearscreen();
    int i = 0;
    for (; i < 25; i++, delayloop())
        printcentered(i, "LOL");
    while (1);
}

void delayloop()
{
    int i = 0;
    while (i++ > 0) ;
}

void clearscreen()
{
    int i = 2000;
    for (; i >= 0; i--)
        *((char*)(0xB8000 + i)) = 0;
}

int strlen(const char* str)
{
    int ret = 0;
    while (*str++)
        ret++;
    return ret;
}

void printcentered(int line, const char* str)
{
    char* vbuf = (char*)0xB8000;
    vbuf += (160 * line) + 80 - (strlen(str) & 0xFE);
    while (*str) {
        *vbuf++ = *str++;
        *vbuf++ = 0x0F;
    }
}
