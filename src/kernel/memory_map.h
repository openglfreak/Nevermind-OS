#define MEMORY_MAP_ATTRIBUTES_USABLE 0x01
#define MEMORY_MAP_ATTRIBUTES_RESERVED 0x02
#define MEMORY_MAP_ATTRIBUTES_ACPI_RECLAIMABLE 0x03
#define MEMORY_MAP_ATTRIBUTES_ACPI_NVS 0x04
#define MEMORY_MAP_ATTRIBUTES_BAD 0x05

typedef struct __attribute__((packed)) {
    uint64_t base;
    uint64_t limit;
    uint32_t attributes;
    uint32_t infos;
} MEMORY_MAP_ENTRY;

typedef struct {
    MEMORY_MAP_ENTRY entries[1024];
} MEMORY_MAP;
