#include <stdint.h>
#include "physical_memory_map.h"
#include "../../../memconsts/memconsts.h"

extern void initialize_physical_memory_manager();

void initialize_memory_manager()
{
    uint32_t i = 2048;
    while (--i)
        physical_memory_map->entries[i] = 0;
    physical_memory_map->entries[0] = PHYSICAL_MEMORY_MAP_ENTRY(physical_memory_map_section0_start,0,0,0); //PHYSICAL_MEMORY_MAP_ENTRY(ar,refpc,s,type)
    i = 0x11;
    while (i--)
        physical_memory_map_section0->entries[i] = PHYSICAL_MEMORY_MAP_SECTION_ENTRY(0,0,PAGE_TYPE_HARDWARE_RESERVED);
    physical_memory_map_section0->entries[0x11] = PHYSICAL_MEMORY_MAP_SECTION_ENTRY(0,0,PAGE_TYPE_PAGE_DIRECTORY);
    physical_memory_map_section0->entries[0x12] = PHYSICAL_MEMORY_MAP_SECTION_ENTRY(1,0,PAGE_TYPE_PAGE_TABLE);
    physical_memory_map_section0->entries[0x13] = PHYSICAL_MEMORY_MAP_SECTION_ENTRY(0,0,PAGE_TYPE_PHYSICAL_MEMORY_MAP);
    physical_memory_map_section0->entries[0x14] = PHYSICAL_MEMORY_MAP_SECTION_ENTRY(1,0,PAGE_TYPE_PHYSICAL_MEMORY_MAP_SECTION);
    i = 0x100;
    while (i-- > 0x16)
        physical_memory_map_section0->entries[i] = PHYSICAL_MEMORY_MAP_SECTION_ENTRY(0,0,PAGE_TYPE_HARDWARE_RESERVED);
    i = 1024;
    while (i--)
        if (hmemmap->entries[i].limit != 0 && hmemmap->entries[i].attributes != HARDWARE_MEMORY_MAP_ATTRIBUTES_USABLE)
        {
            PAGE_INDEX page = POINTER_TO_PAGE_INDEX(hmemmap->entries[i].base);
            uint32_t page_count = (hmemmap->entries[i].limit - hmemmap->entries[i].base + 0xFFF) >> 12;
            PHYSICAL_MEMORY_MAP_SECTION* p = (PHYSICAL_MEMORY_MAP_SECTION*)(physical_memory_map->entries[page.map_entry] & 0xFFFFF000);
            if (physical_memory_map->entries[page.map_entry] == 0)
            {
                
            }
            while (page_count--)
            {
                // TODO: register unusable page
                
                if (++page.section_entry == 0x200)
                {
                    page.section_entry = 0;
                    page.map_entry++;
                    p = (PHYSICAL_MEMORY_MAP_SECTION*)(physical_memory_map->entries[page.map_entry] & 0xFFFFF000);
                }
            }
        }
    //initialize_physical_memory_manager();
}



uint32_t __attribute__ ((used)) allocate_page(uint32_t process_id)
{
    // TODO: implement
    return 0;
}
