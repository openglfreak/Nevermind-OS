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

#define bootcylinders ((unsigned short*)0x7BFB)
#define bootheads ((unsigned char*)0x7BFD)
#define bootsectors ((unsigned char*)0x7BFE)
#define bootdrive ((unsigned char*)0x7BFF)

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
#define memmap_end ((MEMORY_MAP_ENTRY*)0xE000)

#define superblock_start ((SUPERBLOCK*)0xE000)
#define superblock_end ((SUPERBLOCK*)0xE400)

#define root_bgd_start ((BLOCKGROUP_DESCRIPTOR*)0xE400)
#define root_bgd_end ((BLOCKGROUP_DESCRIPTOR*)0xE600)

#define usable_start 0xE600
#define usable_end 0xF000

#define start_file_start 0xF000
#define start_file_end 0x10000

#endif // MEMCONSTS

