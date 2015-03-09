#ifndef _INFOAREA
#define _INFOAREA

typedef struct __attribute__ ((packed)) {
    uint16_t COM1base;
    uint16_t COM2base;
    uint16_t COM3base;
    uint16_t COM4base;
    uint32_t EBDAstart;
} INFOAREA;

#endif // _INFOAREA
