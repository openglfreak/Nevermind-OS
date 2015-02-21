#ifndef _MEMORY_MAP
#define _MEMORY_MAP

#include <stdint.h>

#define HARDWARE_MEMORY_MAP_ATTRIBUTES_BAD 0x05
#define HARDWARE_MEMORY_MAP_ATTRIBUTES_ACPI_NVS 0x04
#define HARDWARE_MEMORY_MAP_ATTRIBUTES_ACPI_RECLAIMABLE 0x03
#define HARDWARE_MEMORY_MAP_ATTRIBUTES_RESERVED 0x02
#define HARDWARE_MEMORY_MAP_ATTRIBUTES_USABLE 0x01

typedef struct __attribute__ ((packed)) {
    uint64_t base;
    uint64_t limit;
    uint32_t attributes;
    uint32_t infos;
} HARDWARE_MEMORY_MAP_ENTRY;

typedef struct {
    HARDWARE_MEMORY_MAP_ENTRY entries[1024];
} HARDWARE_MEMORY_MAP;

#endif // _MEMORY_MAP
