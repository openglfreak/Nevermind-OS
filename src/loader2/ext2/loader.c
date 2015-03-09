#include "../asm.h"
CODE16();
#include "../../memconsts/memconsts.h"
#define setup_wrapper(x) setup(x)
#define setup(s) asm ("movl $"#s",%esp\ncall start\n");
setup_wrapper(stack_end);
#include "superblock.h"
#include "bgdt.h"
#include "inode.h"
#include "directory.h"

#define bootsuperblock ((SUPERBLOCK*)usable_start)
#define bootbgdt ((BLOCKGROUP_DESCRIPTOR_TABLE*)(usable_start+0x0400))

#define GET_DIRVE_PARAMS(d) asm volatile ("mov $0x08,%%ah\n" \
        "int $0x13\n" \
        "movb %%dh,%%al\n" \
        "shll $16,%%eax\n" \
        "movw %%cx,%%ax\n" \
        : "=a" (d) \
        : : "dh", "cx")

#define READ_SECTORS(c,h,s,n,d) asm volatile ("movw %w3,%%bx\n" \
        "shrl $16,%3\n" \
        "movw %w3,%%es\n" \
        "int $0x13\n" \
        : : "a" (0x0200 | ((uint32_t)(n))), "c" ((((uint32_t)(c)) << 8) | ((((uint32_t)(c)) >> 2) & 0xC0) | ((uint32_t)(s))), "d" ((((uint32_t)(h)) << 8) | *bootdrive), "r" ((uint32_t)(d)) \
        : "bx")

typedef struct {
    uint16_t cylinder;
    uint8_t head;
    uint8_t sector;
} CHS;

void __attribute__ ((noreturn)) start();
static CHS lba2chs(uint32_t);
static inline uint32_t block2device(uint32_t);
static inline CHS block2chs(uint32_t);
static INODE* find_file(char*);

static uint32_t blocksize;
static uint32_t blocksize_device;
static uint32_t inodesize;

void __attribute__ ((noreturn,aligned(1))) start()
{
    MOVE_REG_VAR(dl,*bootdrive);
    uint32_t dparams;
    GET_DIRVE_PARAMS(dparams);
    *bootcylinders = (((dparams & 0xC0) << 2) | (dparams >> 8)) + 1;
    *bootheads = ((dparams >> 16) & 0xFF) + 1;
    *bootsectors = dparams & 0x3F;
    CHS chs = lba2chs(2);
    //READ_SECTORS(chs.cylinder,chs.head,chs.sector,2,bootsuperblock);
    asm volatile ("movw %w3,%%bx\n"
        "shrl $16,%3\n"
        "movw %w3,%%es\n"
        "int $0x13\n"
        : : "a" (0x0200 | ((uint32_t)(2))), "c" ((((uint32_t)(chs.cylinder)) << 8) | ((((uint32_t)(chs.cylinder)) >> 2) & 0xC0) | ((uint32_t)(chs.sector))), "d" ((((uint32_t)(chs.head)) << 8) | *((uint8_t*)0x7BFF)), "r" ((uint32_t)(((SUPERBLOCK*)0xB000)))
        : "bx");
    blocksize = 1 << (bootsuperblock->log2_blocksize_sub10 + 10);
    blocksize_device = blocksize >> 9;
    inodesize = 128;
    if (!(bootsuperblock->major_version))
        inodesize = ((EXTENDED_SUPERBLOCK*)&bootsuperblock->reserved)->inode_size;
    chs = lba2chs(bootsuperblock->log2_blocksize_sub10 == 0 ? 4 : blocksize_device);
    READ_SECTORS(chs.cylinder,chs.head,chs.sector,blocksize_device,bootbgdt);
    find_file("start.bin");
    while (1) ;
}

static CHS lba2chs(uint32_t lba)
{
    CHS ret;
    ret.sector = ((lba) % *bootsectors) + 1;
    lba /= *bootsectors;
    ret.head = lba % *bootheads;
    ret.cylinder = lba / *bootheads;
    return ret;
}

static inline uint32_t block2device(uint32_t block)
{
    return block * blocksize_device;
}

static inline CHS block2chs(uint32_t block)
{
    return lba2chs(block2device(block));
}

static INODE* read_inode(uint32_t inode, void* dest)
{
    uint32_t blockgroup = (inode - 1) / bootsuperblock->inodes_per_blockgroup;
    uint32_t index = (inode - 1) % bootsuperblock->inodes_per_blockgroup;
    uint32_t block = (index * inodesize) / blocksize;
    INODE* inode_table = (INODE*)(bootbgdt+blocksize);
    CHS chs = block2chs(bootbgdt[blockgroup]->inode_table_start_block + block);
    READ_SECTORS(chs.cylinder,chs.head,chs.sector,blocksize_device,inode_table);
    return &inode_table[index % (blocksize / inodesize)];
}

#define find_file_direct(a,b) 0

static INODE* find_file(char* name)
{
    INODE* inode_table = (INODE*)(bootbgdt+blocksize);
    CHS chs = block2chs(bootbgdt[0]->inode_table_start_block);
    READ_SECTORS(chs.cylinder,chs.head,chs.sector,blocksize_device,inode_table);
    DIRECTORY_ENTRY* direntry_table = (DIRECTORY_ENTRY*)(inode_table+blocksize);
    int inode = 0;
    uint32_t n = inode_table->disk_sectors_occupied;
    uint32_t i = 0;
    for (; i < 12 && n; i++)
    {
        chs = block2chs(inode_table[1].direct_block_pointers[i]);
        READ_SECTORS(chs.cylinder,chs.head,chs.sector,blocksize_device,direntry_table);
        inode = find_file_direct(name, direntry_table);
        if (inode == 0)
            return read_inode(inode, inode_table);
        n -= blocksize_device;
    }
    return 0;
}

asm (". = 0x50\n"
    ".byte 0x55\n"
    ".byte 0xAA\n");
