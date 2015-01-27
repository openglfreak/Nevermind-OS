#ifndef MEMCONSTS
#define MEMCONSTS

#include <stdint.h>
#include "../kernel/memory/memory_map.h"
#include "../kernel/protected_mode/gdt.h"
#include "../kernel/protected_mode/idt.h"
#include "../kernel/infoarea.h"
#include "../kernel/protected_mode/paging.h"
#include "../kernel/memory/manager/physical_memory_usage_map.h"
#include "../kernel/memory/manager/virtual_memory_usage_map.h"

#define stack_start 0x7B00
#define stack_end 0x7BF0

#define bootcylinders ((uint16_t*)0x7BFB)
#define bootheads ((uint8_t*)0x7BFD)
#define bootsectors ((uint8_t*)0x7BFE)
#define bootdrive ((uint8_t*)0x7BFF)

#define memmap_start ((MEMORY_MAP_ENTRY*)0x7E00)
#define memmap_end ((MEMORY_MAP_ENTRY*)0x8000)
#define memmap ((MEMORY_MAP*)memmap_start)

#define gdt_start ((GDT_ENTRY*)0x8000)
#define gdt_end ((GDT_ENTRY*)0xA000)
#define gdt ((GDT*)gdt_start)

#define idt_start ((IDT_ENTRY*)0xA000)
#define idt_end ((IDT_ENTRY*)0xA800)
#define idt ((IDT*)idt_start)

#define infoarea_start ((INFOAREA*)0xA800)
#define infoarea_end 0xB000
#define infoarea infoarea_start

#define usable_start 0xB000
#define usable_end 0xF000

#define start_file_start 0xF000
#define start_file_end 0x10000

#define cpuid_signature ((uint32_t*)0x10000)
#define cpuid_features0 ((uint32_t*)0x10004)
#define cpuid_features1 ((uint32_t*)0x10008)
#define cpuid_features ((uint64_t*)0x10004)

#define pdir_start ((PAGE_DIRECTORY_ENTRY*)0x11000)
#define pdir_end ((PAGE_DIRECTORY_ENTRY*)0x12000)
#define pdir ((PAGE_DIRECTORY*)pdir_start)
#define ptable0_start ((PAGE_TABLE_ENTRY*)0x12000)
#define ptable0_end ((PAGE_TABLE_ENTRY*)0x13000)
#define ptable0 ((PAGE_TABLE*)ptable0_start)

#define physical_memory_usage_map_start ((PHYSICAL_MEMORY_USAGE_MAP_ENTRY*)0x13000)
#define physical_memory_usage_map_end ((PHYSICAL_MEMORY_USAGE_MAP_ENTRY*)0x14000)
#define physical_memory_usage_map ((PHYSICAL_MEMORY_USAGE_MAP*)physical_memory_usage_map_start)
#define virtual_memory_usage_map_start ((VIRTUAL_MEMORY_USAGE_MAP_ENTRY*)0x14000)
#define virtual_memory_usage_map_end ((VIRTUAL_MEMORY_USAGE_MAP_ENTRY*)0x15000)
#define virtual_memory_usage_map ((VIRTUAL_MEMORY_USAGE_MAP*)virtual_memory_usage_map_start)

#endif // MEMCONSTS

