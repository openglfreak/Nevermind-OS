#ifndef _PHYSICAL_MEMORY_USAGE_MAP
#define _PHYSICAL_MEMORY_USAGE_MAP

#include <stdint.h>

#ifndef _PAGE_INDEX
#define _PAGE_INDEX

#define PAGE_TO_POINTER(p) (p<<12)
#define PAGE_INDEX_TO_PAGE(p) (((p)->map_entry<<9)+(p)->page_entry)
#define PAGE_INDEX_TO_POINTER(p) PAGE_TO_POINTER(PAGE_INDEX_TO_PAGE(p))

#define POINTER_TO_PAGE(p) (p>>12)
#define PAGE_TO_PAGE_INDEX(p) {\
            .map_entry = (p) >> 9,\
            .page_entry = (p) & 0x1FF\
        }
#define POINTER_TO_PAGE_INDEX(p) PAGE_TO_PAGE_INDEX(POINTER_TO_PAGE(p))

typedef struct {
    uint32_t map_entry;
    uint32_t page_entry;
} PAGE_INDEX;

#endif // _PAGE_INDEX

#define PHYSICAL_MEMORY_USAGE_PAGE_REFERENCE_COUNT(c) ((c)<<0x0C)
#define PHYSICAL_MEMORY_USAGE_PAGE_UNINITIALIZED 0x10
#define PHYSICAL_MEMORY_USAGE_PAGE_TYPE_PHYSICAL_USAGE_MAP 0x0F
#define PHYSICAL_MEMORY_USAGE_PAGE_TYPE_PHYSICAL_USAGE_PAGE 0x0E
#define PHYSICAL_MEMORY_USAGE_PAGE_TYPE_VIRTUAL_USAGE_MAP 0x0D
#define PHYSICAL_MEMORY_USAGE_PAGE_TYPE_VIRTUAL_USAGE_PAGE 0x0C
#define PHYSICAL_MEMORY_USAGE_PAGE_TYPE_PAGE_DIRECTORY 0x0B
#define PHYSICAL_MEMORY_USAGE_PAGE_TYPE_PAGE_TABLE 0x0A
#define PHYSICAL_MEMORY_USAGE_PAGE_TYPE_USER_ALLOCATED 0x04
#define PHYSICAL_MEMORY_USAGE_PAGE_TYPE_KERNEL_ALLOCATED 0x03
#define PHYSICAL_MEMORY_USAGE_PAGE_TYPE_SOFTWARE_RESERVED 0x02
#define PHYSICAL_MEMORY_USAGE_PAGE_TYPE_HARDWARE_RESERVED 0x01
#define PHYSICAL_MEMORY_USAGE_PAGE_TYPE_UNALLOCATED 0x00
#define PHYSICAL_MEMORY_USAGE_PAGE_TYPE(t) (t&0x0F)
#define PHYSICAL_MEMORY_USAGE_PAGE(refc,u,t) \
        (PHYSICAL_MEMORY_USAGE_PAGE_REFERENCE_COUNT(refc) |\
        ((u)?PHYSICAL_MEMORY_USAGE_PAGE_UNINITIALIZED:0x00) |\
        PHYSICAL_MEMORY_USAGE_PAGE_TYPE(t))

#define PHYSICAL_MEMORY_USAGE_MAP_ADDRESS(a) (((uint32_t)(a))&0xFFFFF000)
#define PHYSICAL_MEMORY_USAGE_MAP_SIZE_4KB 0x00
#define PHYSICAL_MEMORY_USAGE_MAP_SIZE_4MB 0x80
#define PHYSICAL_MEMORY_USAGE_MAP(addr,s) \
        (PHYSICAL_MEMORY_USAGE_MAP_ADDRESS(addr) |\
        ((s)?PHYSICAL_MEMORY_USAGE_MAP_SIZE_4MB:PHYSICAL_MEMORY_USAGE_MAP_SIZE_4KB))

typedef uint64_t PHYSICAL_MEMORY_USAGE_PAGE_ENTRY;
typedef uint32_t PHYSICAL_MEMORY_USAGE_MAP_ENTRY;

typedef struct __attribute__((aligned(0x1000))) {
    PHYSICAL_MEMORY_USAGE_PAGE_ENTRY entries[512];
} PHYSICAL_MEMORY_USAGE_PAGE;

typedef struct __attribute__((aligned(0x1000))) {
    PHYSICAL_MEMORY_USAGE_MAP_ENTRY pages[2048];
} PHYSICAL_MEMORY_USAGE_MAP;

#endif // _PHYSICAL_MEMORY_USAGE_MAP
