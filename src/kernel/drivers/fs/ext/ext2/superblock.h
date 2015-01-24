#ifndef SUPERBLOCK
#define SUPERBLOCK

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

typedef __attribute__ ((packed)) {
    unsigned int inodes_count;
    unsigned int blocks_count;
    unsigned int reserved_blocks_count;
    unsigned int unallocated_blocks_count;
    unsigned int unallocated_inodes_count;
    unsigned int superblock_block;
    int log2_blocksize_sub10;
    int log2_fragmentsize_sub10;
    unsigned int blocks_per_blockgroup;
    unsigned int fragments_per_blockgroup;
    unsigned int inodes_per_blockgroup;
    int last_mount;
    int last_written;
    unsigned short mounts_since_last_check;
    unsigned short max_mounts_before_check;
    unsigned short ext2_signature;
    unsigned short fs_state;
    unsigned short action_on_error;
    unsigned short minor_version;
    int last_check;
    int check_interval;
    unsigned int creator_os_id;
    unsigned int major_version;
    unsigned short superuser_user_id;
    unsigned short superuser_group_id;
    unsigned char[940] reserved;
} SUPERBLOCK;

#define OPTIONAL_FEATURES_PREALLOCATE_DIRECTORY_BLOCKS 0x01
#define OPTIONAL_FEATURES_AFS_SERVER_INODE_PRESENT 0x02
#define OPTIONAL_FEATURES_HAS_JOURNAL 0x04
#define OPTIONAL_FEATURES_INODE_EXTENDED_ATTRIBUTES 0x08
#define OPTIONAL_FEATURES_CAN_RESIZE 0x10
#define OPTIONAL_FEATURES_DIRECTORY_HASH_INDEX 0x10

typedef __attribute__ ((packed)) {
    unsigned int first_usable_inode;
    unsigned short inode_size;
    unsigned short this_blockgroup;
    unsigned int optional_features;
    unsigned int required_features;
    unsigned int write_required_features;
    unsigned int fs_id[4];
    char volume_name[16];
    char last_mount_path[64];
    unsigned int compression_algorithms;
    unsigned char preallocated_file_blocks;
    unsigned char preallocated_directory_blocks;
    unsigned short unused;
    unsigned int journal_id[4];
    unsigned int journal_inode;
    unsigned int journal_device;
    unsigned int orphan_inodes_head;
} EXTENDED_SUPERBLOCK;

#endif // SUPERBLOCK
