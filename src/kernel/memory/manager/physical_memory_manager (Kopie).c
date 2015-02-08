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
            PHYSICAL_MEMORY_USAGE_PAGE* physical_memory_usage_page = (PHYSICAL_MEMORY_USAGE_PAGE*)(e & 0xFFFFF000);
            for (page.page_entry = 0; page.page_entry < 512; page.page_entry++)
                if (physical_memory_usage_page->entries[page.page_entry] == 0)
                    free_physical_pages++;
                else
                    used_physical_pages++;
        }
    }
}

PAGE_INDEX get_free_physical_page_index()
{
    PAGE_INDEX page;
    for (page.map_entry = 0; page.map_entry < 2048; page.map_entry++)
    {
        PHYSICAL_MEMORY_USAGE_MAP_ENTRY e = physical_memory_usage_map->pages[page.map_entry];
        if (e != 0)
        {
            PHYSICAL_MEMORY_USAGE_PAGE* physical_memory_usage_page = (PHYSICAL_MEMORY_USAGE_PAGE*)(e & 0xFFFFF000);
            for (page.page_entry = 0; page.page_entry < 512; page.page_entry++)
                if (physical_memory_usage_page->entries[page.page_entry] == 0)
                    goto found;
        }
    }
    goto error;
    found:
    if (free_physical_pages == 1)
    {
        ((PHYSICAL_MEMORY_USAGE_PAGE*)(physical_memory_usage_map->pages[page.map_entry] & 0xFFFFF000))->entries[page.page_entry] = PHYSICAL_MEMORY_USAGE_PAGE(1,0,PHYSICAL_MEMORY_USAGE_PAGE_TYPE_PHYSICAL_USAGE_PAGE);
        for (page.map_entry = 0; page.map_entry < 2048; page.map_entry++)
            if (physical_memory_usage_map->pages[page.map_entry] == 0)
            {
                physical_memory_usage_map->pages[page.map_entry] = PHYSICAL_MEMORY_USAGE_MAP((page.map_entry << 21) | (page.page_entry << 12),0);
                page.page_entry = 0;
                return page;
            }
    }
    else
        return page;
    error:
    page.map_entry = 0;
    page.page_entry = 0; // panic
    ret:
    return page;
}

uint32_t get_free_physical_page()
{
    PAGE_INDEX page = get_free_physical_page_index();
    return page.map_entry << 9 | page.page_entry;
}

uint32_t allocate_physical_page(uint32_t kernel)
{
    PAGE_INDEX page = get_free_physical_page_index();
    free_physical_pages--;
    used_physical_pages++;
    PHYSICAL_MEMORY_USAGE_PAGE* physical_memory_usage_page = (PHYSICAL_MEMORY_USAGE_PAGE*)(physical_memory_usage_map->pages[page.map_entry] & 0xFFFFF000);
    physical_memory_usage_page->entries[page.page_entry] = PHYSICAL_MEMORY_USAGE_PAGE(0,1,kernel?PHYSICAL_MEMORY_USAGE_PAGE_TYPE_KERNEL_ALLOCATED:PHYSICAL_MEMORY_USAGE_PAGE_TYPE_USER_ALLOCATED);
    return page.map_entry << 9 | page.page_entry;
}
