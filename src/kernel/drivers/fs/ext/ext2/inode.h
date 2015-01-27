#ifndef INODE
#define INODE

#include <stdint.h>

#define INODE_TYPE_FIFO 0x1000
#define INODE_TYPE_CHARACTER_DEVICE 0x2000
#define INODE_TYPE_DIRECTORY 0x4000
#define INODE_TYPE_BLOCK_DEVICE 0x6000
#define INODE_TYPE_FILE 0x8000
#define INODE_TYPE_SYMBOLIC_LINK 0xA000
#define INODE_TYPE_SOCKET 0xC000

#define INODE_PERMISSION_OTHER_EXECUTE 0x01
#define INODE_PERMISSION_OTHER_WRITE 0x02
#define INODE_PERMISSION_OTHER_READ 0x04
#define INODE_PERMISSION_GROUP_EXECUTE 0x08
#define INODE_PERMISSION_GROUP_WRITE 0x10
#define INODE_PERMISSION_GROUP_READ 0x20
#define INODE_PERMISSION_USER_EXECUTE 0x40
#define INODE_PERMISSION_USER_WRITE 0x80
#define INODE_PERMISSION_USER_READ 0x0100
#define INODE_PERMISSION_STICKY 0x0200
#define INODE_PERMISSION_SET_GROUPID 0x0400
#define INODE_PERMISSION_SET_USERID 0x0800

#define INODE_FLAGS_SECURE_DELETION 0x01
#define INODE_FLAGS_KEEP_COPY 0x02
#define INODE_FLAGS_COMPRESSED 0x04
#define INODE_FLAGS_SYNCHRONOUS 0x08
#define INODE_FLAGS_IMMUTABLE 0x10
#define INODE_FLAGS_APPEND_ONLY 0x20
#define INODE_FLAGS_NO_DUMP_INCLUDE 0x40
#define INODE_FLAGS_NO_LAST_ACCESSED_UPDATE 0x80
#define INODE_FLAGS_HASH_INDEXED 0x010000
#define INODE_FLAGS_AFS_DIRECTORY 0x020000
#define INODE_FLAGS_JOURNAL_FILE_DATA 0x040000

typedef struct __attribute__ ((packed)) {
    uint16_t type_and_permissions;
    uint16_t user_id;
    uint32_t size_low;
    int32_t last_access;
    int32_t creation;
    int32_t last_modify;
    int32_t deletion;
    uint16_t group_id;
    uint16_t hardlink_count;
    uint32_t disk_sectors_occupied;
    uint32_t flags;
    uint32_t os_specific0;
    uint32_t direct_block_pointers[12];
    uint32_t indirect_block_pointer;
    uint32_t doubly_indirect_block_pointer;
    uint32_t triply_indirect_block_pointer;
    uint32_t generation_number;
    uint32_t file_acl;
    uint32_t size_high_or_directory_acl;
    uint32_t fragment;
    uint32_t[3] os_specific1;
} INODE;

#define INODE_AUTHOR_NORMAL 0xFFFFFFFF

typedef struct __attribute__ ((packed)) {
    uint8_t fragment_number;
    uint8_t fragment_size;
    uint16_t type_and_permissions_high;
    uint16_t user_id_high;
    uint16_t group_id_high;
    uint16_t author_id_high;
} OS_SPECIFIC_VALUE1;

#endif // INODE
