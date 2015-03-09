#ifndef BGDT
#define BGDT

typedef struct __attribute__ ((packed)) {
    uint32_t block_usage_bitmap_block;
    uint32_t inode_usage_bitmap_block;
    uint32_t inode_table_start_block;
    uint16_t unallocated_blocks_count;
    uint16_t unallocated_inodes_count;
    uint16_t directories_count;
    uint8_t unused[14];
} BLOCKGROUP_DESCRIPTOR;

typedef BLOCKGROUP_DESCRIPTOR* BLOCKGROUP_DESCRIPTOR_TABLE;

#endif // BGDT
