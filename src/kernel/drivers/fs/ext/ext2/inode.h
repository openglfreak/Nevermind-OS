#ifndef INODE
#define INODE

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
    unsigned short type_and_permissions;
    unsigned short user_id;
    unsigned int size_low;
    int last_access;
    int creation;
    int last_modify;
    int deletion;
    unsigned short group_id;
    unsigned short hardlink_count;
    unsigned int disk_sectors_occupied;
    unsigned int flags;
    unsigned int os_specific0;
    unsigned int direct_block_pointers[12];
    unsigned int indirect_block_pointer;
    unsigned int doubly_indirect_block_pointer;
    unsigned int triply_indirect_block_pointer;
    unsigned int generation_number;
    unsigned int file_acl;
    unsigned int size_high_or_directory_acl;
    unsigned int fragment;
    unsigned int[3] os_specific1;
} INODE;

#define INODE_AUTHOR_NORMAL 0xFFFFFFFF

typedef struct __attribute__ ((packed)) {
    unsigned char fragment_number;
    unsigned char fragment_size;
    unsigned short type_and_permissions_high;
    unsigned short user_id_high;
    unsigned short group_id_high;
    unsigned short author_id_high;
} OS_SPECIFIC_VALUE1;

#endif // INODE
