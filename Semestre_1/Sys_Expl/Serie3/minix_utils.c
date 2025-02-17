#include "minix.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SUPERBLOCK_OFFSET 1024

superblock_t *read_superblock(int fd) {
  superblock_t *sb = malloc(sizeof(superblock_t));
  if (!sb) {
    perror("Failed to allocate memory for superblock");
    return NULL;
  }

  if (lseek(fd, SUPERBLOCK_OFFSET, SEEK_SET) == -1) {
    perror("Failed to seek to superblock");
    free(sb);
    return NULL;
  }

  if (read(fd, sb, sizeof(superblock_t)) != sizeof(superblock_t)) {
    perror("Failed to read superblock");
    free(sb);
    return NULL;
  }

  return sb;
}

uint8_t *read_inodes_bitmap(int fd, superblock_t *sb) {
  int bitmap_size = sb->imap_blocks * BLOCK_SIZE;
  uint8_t *inode_bitmap = malloc(bitmap_size);
  if (!inode_bitmap) {
    perror("Failed to allocate memory for inode bitmap");
    return NULL;
  }

  if (lseek(fd, SUPERBLOCK_OFFSET + BLOCK_SIZE, SEEK_SET) == -1) {
    perror("Failed to seek to inode bitmap");
    free(inode_bitmap);
    return NULL;
  }

  if (read(fd, inode_bitmap, bitmap_size) != bitmap_size) {
    perror("Failed to read inode bitmap");
    free(inode_bitmap);
    return NULL;
  }

  return inode_bitmap;
}

inode_t *read_inodes_table(int fd, superblock_t *sb) {
  int inode_table_size = sb->ninodes * sizeof(inode_t);
  inode_t *inodes = malloc(inode_table_size);
  if (!inodes) {
    perror("Failed to allocate memory for inode table");
    return NULL;
  }

  int inode_table_offset =
      SUPERBLOCK_OFFSET + BLOCK_SIZE * (1 + sb->imap_blocks + sb->zmap_blocks);
  if (lseek(fd, inode_table_offset, SEEK_SET) == -1) {
    perror("Failed to seek to inode table");
    free(inodes);
    return NULL;
  }

  if (read(fd, inodes, inode_table_size) != inode_table_size) {
    perror("Failed to read inode table");
    free(inodes);
    return NULL;
  }

  return inodes;
}
