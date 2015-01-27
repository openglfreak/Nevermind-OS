#include <stdint.h>
#include "physical_memory_usage_map.h"
#include "virtual_memory_usage_map.h"
#include "../../../memconsts/memconsts.h"

void __attribute__ ((used)) initialize_memory_manager()
{
    int i = 512;
    while (--i)
        physical_memory_usage_map->pages[i] = 0;
    physical_memory_usage_map->pages[0] = PHYSICAL_MEMORY_USAGE_MAP(0,1) | VIRTUAL_MEMORY_USAGE_PAGE(addr,VIRTUAL_MEMORY_USAGE_PAGE_TYPE_KERNEL_ALLOCATED);
}
