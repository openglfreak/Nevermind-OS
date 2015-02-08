#include <stdint.h>
#include "physical_memory_usage_map.h"
#include "virtual_memory_usage_map.h"
#include "../../../memconsts/memconsts.h"

extern void initialize_physical_memory_manager();

void initialize_memory_manager()
{
    uint32_t i = 2048;
    while (--i)
        physical_memory_usage_map->pages[i] = 0;
    physical_memory_usage_map->pages[0] = PHYSICAL_MEMORY_USAGE_MAP(physical_memory_usage_page0_start,0);
    i = 0x11;
    while (i--)
        physical_memory_usage_page0->entries[i] = PHYSICAL_MEMORY_USAGE_PAGE(0,0,PHYSICAL_MEMORY_USAGE_PAGE_TYPE_HARDWARE_RESERVED);
    physical_memory_usage_page0->entries[0x11] = PHYSICAL_MEMORY_USAGE_PAGE(0,0,PHYSICAL_MEMORY_USAGE_PAGE_TYPE_PAGE_DIRECTORY);
    physical_memory_usage_page0->entries[0x12] = PHYSICAL_MEMORY_USAGE_PAGE(1,0,PHYSICAL_MEMORY_USAGE_PAGE_TYPE_PAGE_TABLE);
    physical_memory_usage_page0->entries[0x13] = PHYSICAL_MEMORY_USAGE_PAGE(0,0,PHYSICAL_MEMORY_USAGE_PAGE_TYPE_PHYSICAL_USAGE_MAP);
    physical_memory_usage_page0->entries[0x14] = PHYSICAL_MEMORY_USAGE_PAGE(1,0,PHYSICAL_MEMORY_USAGE_PAGE_TYPE_PHYSICAL_USAGE_PAGE);
    physical_memory_usage_page0->entries[0x15] = PHYSICAL_MEMORY_USAGE_PAGE(0,0,PHYSICAL_MEMORY_USAGE_PAGE_TYPE_VIRTUAL_USAGE_PAGE);
    i = 0x100;
    while (i-- > 0x16)
        physical_memory_usage_page0->entries[i] = PHYSICAL_MEMORY_USAGE_PAGE(0,0,PHYSICAL_MEMORY_USAGE_PAGE_TYPE_SOFTWARE_RESERVED);
    i = 1024;
    while (i--)
        if (memmap->entries[i].limit != 0 && memmap->entries[i].__attribute__s != MEMORY_MAP_ATTRIBUTES_USABLE)
        {
            PAGE_INDEX page = POINTER_TO_PAGE_INDEX(memmap->entries[i].base);
            uint32_t page_count = (memmap->entries[i].limit - memmap->entries[i].base + 0xFFF) >> 12;
            PHYSICAL_MEMORY_USAGE_PAGE* p = (PHYSICAL_MEMORY_USAGE_PAGE*)(physical_memory_usage_map->pages[page.map_entry] & 0xFFFFF000);
            if (physical_memory_usage_map->pages[page.map_entry] == 0)
            {
                
            }
            while (page_count--)
            {
                // TODO: register unusable page
                
                if (++page.page_entry == 0x200)
                {
                    page.page_entry = 0;
                    page.map_entry++;
                    p = (PHYSICAL_MEMORY_USAGE_PAGE*)(physical_memory_usage_map->pages[page.map_entry] & 0xFFFFF000);
                }
            }
        }
    initialize_physical_memory_manager();
}



uint32_t __attribute__ ((used)) allocate_page(uint32_t process_id)
{
    // TODO: implement
    return 0;
}
