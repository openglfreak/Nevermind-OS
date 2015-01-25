#ifndef MEMCONSTS
#define MEMCONSTS

#include "../kernel/gdt.h"
#include "../kernel/idt.h"
#include "../kernel/paging.h"
#include "../kernel/infoarea.h"
#include "../kernel/memory_map.h"
#include "../kernel/drivers/fs/ext/ext2/superblock.h"
#include "../kernel/drivers/fs/ext/ext2/bgdt.h"

#define stack_start 0x7B00
#define stack_end 0x7BF0

#define bootcylinders ((uint16_t*)0x7BFB)
#define bootheads ((uint8_t*)0x7BFD)
#define bootsectors ((uint8_t*)0x7BFE)
#define bootdrive ((uint8_t*)0x7BFF)

#define gdt_start ((GDT_ENTRY*)0x8000)
#define gdt_end ((GDT_ENTRY*)0xA000)
#define gdt ((GDT*)gdt_start)

#define idt_start ((IDT_ENTRY*)0xA000)
#define idt_end ((IDT_ENTRY*)0xA800)
#define idt ((IDT*)idt_start)

#define infoarea_start ((INFOAREA*)0xA800)
#define infoarea_end 0xB000
#define infoarea infoarea_start

#define pdir_start ((PAGE_DIRECTORY_ENTRY*)0xB000)
#define pdir_end ((PAGE_DIRECTORY_ENTRY*)0xC000)
#define pdir ((PAGE_DIRECTORY*)pdir_start)
#define ptable0_start ((PAGE_TABLE_ENTRY*)0xC000)
#define ptable0_end ((PAGE_TABLE_ENTRY*)0xD000)
#define ptable0 ((PAGE_TABLE*)ptable0_start)

#define memmap_start ((MEMORY_MAP_ENTRY*)0xD000)
#define memmap_end ((MEMORY_MAP_ENTRY*)0xE000)
#define memmap ((MEMORY_MAP*)memmap_start)

#define superblock_start ((SUPERBLOCK*)0xE000)
#define superblock_end 0xE400
#define superblock superblock_start

#define root_bgd_start ((BLOCKGROUP_DESCRIPTOR*)0xE400)
#define root_bgd_end ((BLOCKGROUP_DESCRIPTOR*)0xE600)
#define root_bgd root_bgd_start

#define usable_start 0xE600
#define usable_end 0xF000

#define start_file_start 0xF000
#define start_file_end 0x10000

#endif // MEMCONSTS

