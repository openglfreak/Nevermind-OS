#include <stdint.h>
#include "physical_memory_map.h"
#include "../../../memconsts/memconsts.h"

#define MAP_ALLOCATED(e) (((e)&PHYSICAL_MEMORY_MAP_ENTRY_DIRECT)?((e)>>14||(e)&0x07):(e)>>12)

uint32_t alloc_physical(uint32_t length, uint32_t type)
{
    uint32_t address = 0; //get_free_region_physical(length);
    PAGE_INDEX page;
    page.map_entry = address >> 22;
    page.section_entry = (address >> 12) & 0x03FF;
    while (length > 0)
    {
        if (!MAP_ALLOCATED(physical_memory_map->entries[page.map_entry]))
            if (page.section_entry == 0)
            {
                physical_memory_map->entries[page.map_entry] = PHYSICAL_MEMORY_MAP_ENTRY(1,length<=1024?length-1:1023,1,type);
                page.map_entry++;
                length -= 1024;
                continue;
            }
            else ;
                // TODO: allocate map section
        if (physical_memory_map->entries[page.map_entry]&PHYSICAL_MEMORY_MAP_ENTRY_DIRECT)
        {
            if ((physical_memory_map->entries[page.map_entry] & 0x07) == (type & 0x07) && page.section_entry == ((physical_memory_map->entries[page.map_entry] & 0x3FF0) + 1))
                if (length > 1023 - ((physical_memory_map->entries[page.map_entry] >> 4) & 0x3FF))
                {
                    length -= 1023 - ((physical_memory_map->entries[page.map_entry] >> 4) & 0x3FF);
                    physical_memory_map->entries[page.map_entry] |= PHYSICAL_MEMORY_MAP_ENTRY_REFERENCED_PAGES_COUNT(1024);
                    continue;
                }
                else
                {
                    length = 0;
                    physical_memory_map->entries[page.map_entry] += (1024 - length) << 4;
                    break;
                }
            // TODO: allocate map section
            PHYSICAL_MEMORY_MAP_SECTION* section = 0;
            uint32_t i = (physical_memory_map->entries[page.map_entry] >> 4) & 0x03FF;
            uint32_t refc = (physical_memory_map->entries[page.map_entry] >> 14) / i;
            while (i)
                section->entries[i] = PHYSICAL_MEMORY_MAP_SECTION_ENTRY(0,refc,physical_memory_map->entries[page.map_entry]&0x07);
            physical_memory_map->entries[page.map_entry] = PHYSICAL_MEMORY_MAP_ENTRY(section,((physical_memory_map->entries[page.map_entry]>>4)&0x03FF)+(length>1024?1024:length),0,0);
            while (--length > 0 && page.section_entry < 1024)
                section->entries[page.section_entry++] = PHYSICAL_MEMORY_MAP_SECTION_ENTRY(0,1,type);
            page.map_entry++;
            page.section_entry = 0;
        }
        else
        {
            length -= 1024 - page.section_entry;
            PHYSICAL_MEMORY_MAP_SECTION* section = (PHYSICAL_MEMORY_MAP_SECTION*)(physical_memory_map->entries[page.map_entry]&0xFFFFF000);
            while (page.section_entry < 1024)
                section->entries[page.section_entry++] = PHYSICAL_MEMORY_MAP_SECTION_ENTRY(0,1,type);
            page.map_entry++;
            page.section_entry = 0;
        }
    }
}
