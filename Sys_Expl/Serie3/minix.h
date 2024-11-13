#ifndef _MINIX_H_
#define _MINIX_H_

#include <stdint.h>

#define BLOCK_SIZE 1024
#define MAGIC 0x137F
#define NZONES 9
#define DIRECT_BLOCKS 7

// Number of blocks that can be addressed using a single indirect pointer
#define SINGLE_INDIRECT_BLOCKS (BLOCK_SIZE / sizeof(uint16_t))
// Number of blocks that can be addressed using a double indirect pointer
#define DOUBLE_INDIRECT_BLOCKS (SINGLE_INDIRECT_BLOCKS * SINGLE_INDIRECT_BLOCKS)
// Indirect block index
#define INDIRECT_IDX 7
// Double indirect block index
#define DOUBLE_INDIRECT_IDX 8

// File types
#define TYPE_FIFO 0x1
#define TYPE_CHARDEV 0x2
#define TYPE_DIR 0x4
#define TYPE_BLOCKDEV 0x6
#define TYPE_FILE 0x8
#define TYPE_SYMLINK 0xA

#define INODE_EXTRACT_TYPE(mode) ((mode >> 12) & 0xF)

#define SIZE_TO_BLOCK(size) ((size + (BLOCK_SIZE - 1)) / BLOCK_SIZE)

typedef struct __attribute__((__packed__)) {
  uint16_t ninodes;       // total number of inodes
  uint16_t nzones;        // total number of blocks (including superblock)
  uint16_t imap_blocks;   // inodes bitmap size in blocks
  uint16_t zmap_blocks;   // data blocks bitmap size in blocks
  uint16_t firstdatazone; // index of first data block
  uint16_t log_zone_size; // block size in bytes = 1024*2^s_log_zone_size
  uint32_t max_size;      // max file size in bytes
  uint16_t magic;         // 0x137f = v1 with 14 characters dir_entry
                          // 0x138f = v1 with 30 characters dir_entry
  uint16_t state;         // was the FS properly unmounted?
} superblock_t;

typedef struct __attribute__((__packed__)) {
  uint16_t mode;         // file type and permissions for file
  uint16_t uid;          // user id
  uint32_t size;         // file size in bytes
  uint32_t time;         // inode time
  uint8_t gid;           // group id
  uint8_t nlinks;        // number of path pointing to this inode
  uint16_t zone[NZONES]; // [0..6] = direct pointers, [7] = indirect, [8] double
                         // indirect
} inode_t;

typedef struct __attribute__((__packed__)) {
  uint16_t inode;
  uint8_t name[14];
} dir_entry_t;

extern superblock_t *read_superblock(int fd);
extern inode_t *read_inodes_table(int fd, superblock_t *sb);
extern uint8_t *read_inodes_bitmap(int fd, superblock_t *sb);
extern uint8_t *read_blocks_bitmap(int fd, superblock_t *sb);
extern int get_bit(uint8_t *bitmap, int bit);
extern void read_file(int fd, inode_t *inode);
extern void read_dir(int fd, inode_t *inode);
extern void print_superblock(superblock_t *sb);
extern void print_inode(inode_t *);
extern int namei(int fd, inode_t *inodes, char *path);

#endif