#ifndef SUPERBLOCK
#define SUPERBLOCK

#include <stdint.h>

#define EXT2_SIGNATURE 0xEF53

#define FILE_SYSTEM_STATUS_CLEAN 0x01
#define FILE_SYSTEM_STATUS_ERROR 0x02

#define ERROR_HANDLING_IGNORE 0x01
#define ERROR_HANDLING_MOUNT_READONLY 0x02
#define ERROR_HANDLING_PANIC 0x02

#define CREATOR_OS_LINUX 0x00
#define CREATOR_OS_GNU_HURD 0x01
#define CREATOR_OS_MASIX 0x02
#define CREATOR_OS_FREEBSD 0x03
#define CREATOR_OS_OTHER_BSD44LITE_DERIVATIVES 0x04

typedef struct __attribute__ ((packed)) {
    uint32_t inodes_count;
    uint32_t blocks_count;
    uint32_t reserved_blocks_count;
    uint32_t unallocated_blocks_count;
    uint32_t unallocated_inodes_count;
    uint32_t superblock_block;
    int32_t log2_blocksize_sub10;
    int32_t log2_fragmentsize_sub10;
    uint32_t blocks_per_blockgroup;
    uint32_t fragments_per_blockgroup;
    uint32_t inodes_per_blockgroup;
    int32_t last_mount;
    int32_t last_written;
    uint16_t mounts_since_last_check;
    uint16_t max_mounts_before_check;
    uint16_t ext2_signature;
    uint16_t fs_state;
    uint16_t action_on_error;
    uint16_t minor_version;
    int32_t last_check;
    int32_t check_interval;
    uint32_t creator_os_id;
    uint32_t major_version;
    uint16_t superuser_user_id;
    uint16_t superuser_group_id;
    uint8_t reserved[940];
} SUPERBLOCK;

#define OPTIONAL_FEATURES_PREALLOCATE_DIRECTORY_BLOCKS 0x01
#define OPTIONAL_FEATURES_AFS_SERVER_INODE_PRESENT 0x02
#define OPTIONAL_FEATURES_HAS_JOURNAL 0x04
#define OPTIONAL_FEATURES_INODE_EXTENDED_ATTRIBUTES 0x08
#define OPTIONAL_FEATURES_CAN_RESIZE 0x10
#define OPTIONAL_FEATURES_DIRECTORY_HASH_INDEX 0x10

typedef struct __attribute__ ((packed)) {
    uint32_t first_usable_inode;
    uint16_t inode_size;
    uint16_t this_blockgroup;
    uint32_t optional_features;
    uint32_t required_features;
    uint32_t write_required_features;
    uint32_t fs_id[4];
    int8_t volume_name[16];
    int8_t last_mount_path[64];
    uint32_t compression_algorithms;
    uint8_t preallocated_file_blocks;
    uint8_t preallocated_directory_blocks;
    uint16_t unused;
    uint32_t journal_id[4];
    uint32_t journal_inode;
    uint32_t journal_device;
    uint32_t orphan_inodes_head;
} EXTENDED_SUPERBLOCK;

#endif // SUPERBLOCK
