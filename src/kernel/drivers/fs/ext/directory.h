#ifndef DIRECTORY
#define DIRECTORY

#define DIRECTORY_TYPE_UNKNOWN 0x00
#define DIRECTORY_TYPE_FILE 0x01
#define DIRECTORY_TYPE_DIRECTORY 0x02
#define DIRECTORY_TYPE_CHARACTER_DEVICE 0x03
#define DIRECTORY_TYPE_BLOCK_DEVICE 0x04
#define DIRECTORY_TYPE_FIFO 0x05
#define DIRECTORY_TYPE_SOCKET 0x06
#define DIRECTORY_TYPE_SYMBOLIC_LINK 0x07

typedef struct __attribute__ ((packed)) {
    unsigned int inode;
    unsigned short entry_size;
    unsigned char name_len_low;
    unsigned char name_len_high_or_type;
    char name[];
} DIRECTORY_ENTRY;

#endif // DIRECTORY
