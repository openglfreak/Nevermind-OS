#ifndef _PAGE_INDEX
#define _PAGE_INDEX

#define PAGE_TO_POINTER(p) (p<<12)
#define PAGE_INDEX_TO_PAGE(p) (((p)->map_entry<<10)+((p)->section_entry))
#define PAGE_INDEX_TO_POINTER(p) PAGE_TO_POINTER(PAGE_INDEX_TO_PAGE(p))

#define POINTER_TO_PAGE(p) (p>>12)
#define PAGE_TO_PAGE_INDEX(p) ((PAGE_INDEX){\
            .map_entry = (p) >> 10,\
            .section_entry = (p) & 0x3FF\
        })
#define POINTER_TO_PAGE_INDEX(p) PAGE_TO_PAGE_INDEX(POINTER_TO_PAGE(p))

typedef struct {
    uint16_t map_entry;
    uint16_t section_entry;
} PAGE_INDEX;

#endif // _PAGE_INDEX
