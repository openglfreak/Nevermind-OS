#include <stdint.h>
#include "physical_memory_usage_map.h"
#include "../../../memconsts/memconsts.h"

uint32_t free_physical_pages;
uint32_t allocatable_physical_pages;
uint32_t used_physical_pages;

void __attribute__ ((used)) initialize_physical_memory_manager()
{
    free_physical_pages = 0;
    allocatable_physical_pages = 0;
    used_physical_pages = 0;
    PAGE_INDEX page;
    for (page.map_entry = 0; page.map_entry < 2048; page.map_entry++)
    {
        PHYSICAL_MEMORY_USAGE_MAP_ENTRY e = physical_memory_usage_map->pages[page.map_entry];
        if (e == 0)
            free_physical_pages += 512;
        else
        {
            PHYSICAL_MEMORY_USAGE_PAGE* p = (PHYSICAL_MEMORY_USAGE_PAGE*)(e & 0xFFFFF000);
            for (page.page_entry = 0; page.page_entry < 512; page.page_entry++)
                if (p->entries[page.page_entry] == 0)
                {
                    free_physical_pages++;
                    allocatable_physical_pages++;
                }
                else
                    used_physical_pages++;
        }
    }
}

PAGE_INDEX get_free_physical_pages_start_index(uint32_t nPages)
{
    
}

uint32_t allocate_physical_pages(uint32_t kernel, uint32_t nPages)
{
    
}

uint32_t allocate_physical_pages_at(uint32_t type, uint32_t nPages, uint32_t start_page)
{
    PAGE_INDEX page = PAGE_TO_PAGE_INDEX(start_page);
    while (nPages--)
    {
        
        if (++page.page_entry == 0x200)
        {
            page.page_entry = 0;
            page.map_entry++;
        }
    }
}
