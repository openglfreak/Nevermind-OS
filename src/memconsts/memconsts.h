#ifndef MEMCONSTS
#define MEMCONSTS

#include "../tables/gdt.h"
#include "../tables/idt.h"
#include "../paging.h"
#include "../memory_map.h"

#define bootdrive ((unsigned char*)0x7BFF)

#define root_bgd_start 0x7E00
#define root_bgd_end 0x7E20

#define stack_start ((unsigned short*)0x7E20)
#define stack_end ((unsigned short*)0x8000)

#define infoarea_start ((INFOAREA*)0x8000)
#define infoarea_end ((INFOAREA*)0x8200)

#define gdt_start ((GDT_ENTRY*)0x9000)
#define gdt_end ((GDT_ENTRY*)0xB000)

#define idt_start ((IDT_ENTRY*)0x8200)
#define idt_end ((IDT_ENTRY*)0x9000)

#define pdir_start ((PAGE_DIRECTORY*)0xB000)
#define pdir_end ((PAGE_DIRECTORY_ENTRY*)0xC000)
#define ptable0_start ((PAGE_TABLE*)0xC000)
#define ptable0_end ((PAGE_TABLE_ENTRY*)0xD000)

#define memmap_start ((MEMORY_MAP*)0xD000)
#define memmap_end ((MEMORY_MAP_ENTRY*)0xF000)

#define superblock_start ((SUPERBLOCK*)0xE000)
#define superblock_end ((SUPERBLOCK*)0xE400)

#define usable_start 0xE400

#endif // MEMCONSTS

