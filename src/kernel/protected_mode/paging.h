#ifndef PAGING
#define PAGING

#include <stdint.h>

#define PAGE_DIRECTORY_ADDRESS(a) (((uint32_t)(a))&0xFFFFF000)
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
        (PAGE_DIRECTORY_ADDRESS(addr) |\
        ((s)?PAGE_DIRECTORY_SIZE_4MB:PAGE_DIRECTORY_SIZE_4KB) |\
        ((a)?PAGE_DIRECTORY_ACCESSED:0x00) |\
        ((d)?PAGE_DIRECTORY_NOT_CACHED:PAGE_DIRECTORY_CACHED) |\
        ((w)?PAGE_DIRECTORY_WRITE_THROUGH:PAGE_DIRECTORY_WRITE_BACK) |\
        ((u)?PAGE_DIRECTORY_PRIVILEGE_USER:PAGE_DIRECTORY_PRIVILEGE_SUPERVISOR) |\
        ((r)?PAGE_DIRECTORY_READ_WRITE:PAGE_DIRECTORY_READ_ONLY) |\
        ((p)?PAGE_DIRECTORY_PRESENT:0x00))

#define PAGE_TABLE_ADDRESS(a) (((uint32_t)(a))&0xFFFFF000)
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
        (PAGE_TABLE_ADDRESS(addr) |\
        ((g)?PAGE_TABLE_GLOBAL:0x00) |\
        ((d)?PAGE_TABLE_DIRTY:0x00) |\
        ((a)?PAGE_TABLE_ACCESSED:0x00) |\
        ((c)?PAGE_TABLE_NOT_CACHED:PAGE_TABLE_CACHED) |\
        ((w)?PAGE_TABLE_WRITE_THROUGH:PAGE_TABLE_WRITE_BACK) |\
        ((u)?PAGE_TABLE_PRIVILEGE_USER:PAGE_TABLE_PRIVILEGE_SUPERVISOR) |\
        ((r)?PAGE_TABLE_READ_WRITE:PAGE_TABLE_READ_ONLY) |\
        ((p)?PAGE_TABLE_PRESENT:0x00))

#if TARGET_ARCH == intel && TARGET_ARCH_VERSION >= 486
#define INVALIDATE_PAGE(p) __asm__ __volatile__ ("invlpg (%0)\n" : : "ri" (p) : "memory")
#else
#define INVALIDATE_PAGE(p) INVALIDATE_ALL_PAGES()
#endif // TARGET_ARCH == intel && TARGET_MACHINE >= 486

#define INVALIDATE_ALL_PAGES() do {\
            register uint32_t temp;\
            __asm__ __volatile__ ("movl %%cr3,%0\nmovl %0,%%cr3\n" : "=r"(temp) : : "memory");\
        } while (0)

#define LOAD_PAGE_DIRECTORY(a) __asm__ __volatile__ ("movl %0,%%cr3\n" : : "r" (a) : "memory")

#define SAVE_PAGE_DIRECTORY(var) __asm__ __volatile__ ("movl %%cr3,%0\n" : "=r"(*var))

#define ENABLE_PAGING() do {\
            register uint32_t temp;\
            __asm__ __volatile__ ("movl %%cr0,%0\norl $0x80000000,%0\nmovl %0,%%cr0\n" : "=r"(temp) : : "memory");\
        } while (0)
#define DISABLE_PAGING() do {\
            register uint32_t temp;\
            __asm__ __volatile__ ("movl %%cr0,%0\nandl $0x7FFFFFFF,%0\nmovl %0,%%cr0\n" : "=r"(temp) : : "memory");\
        } while (0)
#define SWITCH_PAGING() do {\
            register uint32_t temp;\
            __asm__ __volatile__ ("movl %%cr0,%0\nxorl $0x80000000,%0\nmovl %0,%%cr0\n" : "=r"(temp) : : "memory");\
        } while (0)

#define ENABLE_PSE() do {\
            register uint32_t temp;\
            __asm__ __volatile__ ("movl %%cr4,%0\norl $0x10,%0\nmovl %0,%%cr4\n" : "=r"(temp) : : "memory");\
        } while (0)
#define DISABLE_PSE() do {\
            register uint32_t temp;\
            __asm__ __volatile__ ("movl %%cr4,%0\nandl $0xFFFFFFEF,%0\nmovl %0,%%cr4\n" : "=r"(temp) : : "memory");\
        } while (0)
#define SWITCH_PSE() do {\
            register uint32_t temp;\
            __asm__ __volatile__ ("movl %%cr4,%0\nxorl $0x10,%0\nmovl %0,%%cr4\n" : "=r"(temp) : : "memory");\
        } while (0)

#define ENABLE_PAGING_PSE() do {\
            register uint32_t temp;\
            __asm__ __volatile__ ("movl %%cr4,%0\norl $0x10,%0\nmovl %0,%%cr4\n"\
                    "movl %%cr0,%0\norl $0x80000000,%0\nmovl %0,%%cr0\n" : "=r"(temp) : : "memory");\
        } while (0)
#define DISABLE_PAGING_PSE() do {\
            register uint32_t temp;\
            __asm__ __volatile__ ("movl %%cr4,%0\nandl $0xFFFFFFEF,%0\nmovl %0,%%cr4\n"\
                    "movl %%cr0,%0\nandl $0x7FFFFFFF,%0\nmovl %0,%%cr0\n" : "=r"(temp) : : "memory");\
        } while (0)
#define SWITCH_PAGING_PSE() do {\
            register uint32_t temp;\
            __asm__ __volatile__ ("movl %%cr4,%0\nxorl $0x10,%0\nmovl %0,%%cr4\n"\
                    "movl %%cr0,%0\nxorl $0x80000000,%0\nmovl %0,%%cr0\n" : "=r"(temp) : : "memory");\
        } while (0)

typedef uint32_t PAGE_DIRECTORY_ENTRY;
typedef uint32_t PAGE_TABLE_ENTRY;

typedef struct {
    PAGE_DIRECTORY_ENTRY entries[1024];
} PAGE_DIRECTORY;

typedef struct __attribute__((aligned(0x1000))) {
    PAGE_TABLE_ENTRY entries[1024];
} PAGE_TABLE;

#endif // PAGING
