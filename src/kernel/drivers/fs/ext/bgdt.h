#ifndef BGDT
#define BGDT

typedef struct {
    BLOCKGROUP_DESCRIPTOR descriptors[];
} BLOCKGROUP_DESCRIPTOR_TABLE;

typedef struct __attribute__ ((packed)) {
    unsigned int block_usage_bitmap_block;
    unsigned int inode_usage_bitmap_block;
    unsigned int inode_table_start_block;
    unsigned short unallocated_blocks_count;
    unsigned short unallocated_inodes_count;
    unsigned short directories_count;
    unsigned char unused[13];
} BLOCKGROUP_DESCRIPTOR;

#endif // BGDT
