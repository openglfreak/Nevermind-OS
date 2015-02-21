#ifndef _VIRTUAL_MEMORY_USAGE_MAP
#define _VIRTUAL_MEMORY_USAGE_MAP

#include <stdint.h>
#include "page_index.h"

#define VIRTUAL_MEMORY_USAGE_PAGE_PROCESS_ID(i) ((i)<<0x20)
#define VIRTUAL_MEMORY_USAGE_PAGE_PHYSICAL_ADDRESS(a) (((uint32_t)(a))&0xFFFFF000)
#define VIRTUAL_MEMORY_USAGE_PAGE_TYPE_USER_ALLOCATED 0x03
#define VIRTUAL_MEMORY_USAGE_PAGE_TYPE_KERNEL_ALLOCATED 0x02
#define VIRTUAL_MEMORY_USAGE_PAGE_TYPE_UNALLOCATED 0x00
#define VIRTUAL_MEMORY_USAGE_PAGE_TYPE(t) (t&0x0F)
#define VIRTUAL_MEMORY_USAGE_PAGE(addr,t) \
        (VIRTUAL_MEMORY_USAGE_PAGE_PHYSICAL_ADDRESS(addr) |\
        VIRTUAL_MEMORY_USAGE_PAGE_TYPE(t))

#define VIRTUAL_MEMORY_USAGE_MAP_ADDRESS(a) (((uint32_t)(a))&0xFFFFF000)
#define VIRTUAL_MEMORY_USAGE_MAP_SIZE_4KB 0x00
#define VIRTUAL_MEMORY_USAGE_MAP_SIZE_4MB 0x80
#define VIRTUAL_MEMORY_USAGE_MAP_ALLOCATED 0x01
#define VIRTUAL_MEMORY_USAGE_MAP(addr,s,a) \
        (VIRTUAL_MEMORY_USAGE_MAP_ADDRESS(addr) |\
        ((s)?VIRTUAL_MEMORY_USAGE_MAP_SIZE_4MB:VIRTUAL_MEMORY_USAGE_MAP_SIZE_4KB) |\
        ((a)?VIRTUAL_MEMORY_USAGE_MAP_ALLOCATED:0x00))

typedef uint64_t VIRTUAL_MEMORY_USAGE_PAGE_ENTRY;
typedef uint32_t VIRTUAL_MEMORY_USAGE_MAP_ENTRY;

typedef struct __attribute__((aligned(0x1000))) {
    VIRTUAL_MEMORY_USAGE_PAGE_ENTRY entries[512];
} VIRTUAL_MEMORY_USAGE_PAGE;

typedef struct __attribute__((aligned(0x1000))) {
    VIRTUAL_MEMORY_USAGE_MAP_ENTRY pages[2048];
} VIRTUAL_MEMORY_USAGE_MAP;

#endif // _VIRTUAL_MEMORY_USAGE_MAP
