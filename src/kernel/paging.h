#ifndef PAGING
#define PAGING

#define PAGE_DIRECTORY_ADDRESS(a) ((a)&0xFFFFF000)
#define PAGE_DIRECTORY_SIZE_4KB 0x00
#define PAGE_DIRECTORY_SIZE_4MB 0x80
#define PAGE_DIRECTORY_ACCESSED 0x20
#define PAGE_DIRECTORY_CACHED 0x00
#define PAGE_DIRECTORY_NOT_CACHED 0x10
#define PAGE_DIRECTORY_WRITE_THROUGH 0x08
#define PAGE_DIRECTORY_WRITE_BACK 0x00
#define PAGE_DIRECTORY_PRIVILEGE_USER 0x04
#define PAGE_DIRECTORY_PRIVILEGE_SUPERVISOR 0x00
#define PAGE_DIRECTORY_READ_WRITE 0x02
#define PAGE_DIRECTORY_READ_ONLY 0x00
#define PAGE_DIRECTORY_PRESENT 0x01
#define PAGE_DIRECTORY(addr,s,a,d,w,u,r,p) \
        PAGE_DIRECTORY_ADDRESS(addr) |\
        ((s)?PAGE_DIRECTORY_SIZE_4MB:PAGE_DIRECTORY_SIZE_4KB) |\
        ((a)?PAGE_DIRECTORY_ACCESSED:0x00) |\
        ((d)?PAGE_DIRECTORY_NOT_CACHED:PAGE_DIRECTORY_CACHED) |\
        ((w)?PAGE_DIRECTORY_WRITE-THROUGH:PAGE_DIRECTORY_WRITE-BACK) |\
        ((u)?PAGE_DIRECTORY_PRIVILEGE_USER:PAGE_DIRECTORY_PRIVILEGE_SUPERVISOR) |\
        ((r)?PAGE_DIRECTORY_READ_WRITE:PAGE_DIRECTORY_READ_ONLY) |\
        ((p)?PAGE_DIRECTORY_PRESENT:0x00))

#define PAGE_TABLE_ADDRESS(a) ((a)&0xFFFFF000)
#define PAGE_TABLE_GLOBAL 0x0100
#define PAGE_TABLE_DIRTY 0x80
#define PAGE_TABLE_ACCESSED 0x40
#define PAGE_TABLE_CACHED 0x00
#define PAGE_TABLE_NOT_CACHED 0x10
#define PAGE_TABLE_WRITE_THROUGH 0x08
#define PAGE_TABLE_WRITE_BACK 0x00
#define PAGE_TABLE_PRIVILEGE_USER 0x04
#define PAGE_TABLE_PRIVILEGE_SUPERVISOR 0x00
#define PAGE_TABLE_READ_WRITE 0x02
#define PAGE_TABLE_READ_ONLY 0x00
#define PAGE_TABLE_PRESENT 0x01
#define PAGE_TABLE(addr,g,d,a,c,w,u,r,p) \
        PAGE_TABLE_ADDRESS(addr) |\
        ((g)?PAGE_TABLE_GLOBAL:0x00) |\
        ((d)?PAGE_TABLE_DIRTY:0x00) |\
        ((a)?PAGE_TABLE_ACCESSED:0x00) |\
        ((c)?PAGE_TABLE_NOT_CACHED:PAGE_TABLE_CACHED) |\
        ((w)?PAGE_TABLE_WRITE-THROUGH:PAGE_TABLE_WRITE-BACK) |\
        ((u)?PAGE_TABLE_PRIVILEGE_USER:PAGE_TABLE_PRIVILEGE_SUPERVISOR) |\
        ((r)?PAGE_TABLE_READ_WRITE:PAGE_TABLE_READ_ONLY) |\
        ((p)?PAGE_TABLE_PRESENT:0x00))

#if TARGET_ARCH == intel && TARGET_ARCH_VERSION >= 486
#define INVALIDATE_PAGE(p) __asm__ __volatile__ ("invlpg (%0)\n" : : "r" (p))
#else
#define INVALIDATE_PAGE(p) INVALIDATE_ALL_PAGES
#endif // TARGET_ARCH == intel && TARGET_MACHINE >= 486

#define INVALIDATE_ALL_PAGES() __asm__ __volatile__ ("movl %%cr3,%%eax\nmovl %%eax,%%cr3\n" : : : "eax")

typedef unsigned int PAGE_DIRECTORY_ENTRY;
typedef unsigned int PAGE_TABLE_ENTRY;

typedef struct {
    PAGE_DIRECTORY_ENTRY entries[1024];
} PAGE_DIRECTORY;

typedef struct {
    PAGE_TABLE_ENTRY entries[1024];
} PAGE_TABLE;

#endif // PAGING
