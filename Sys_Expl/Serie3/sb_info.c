#include "minix.h"
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void display_superblock_info(superblock_t *sb) {
  printf("File System Signature: 0x%x\n", sb->magic);
  printf("Total Number of Inodes: %u\n", sb->ninodes);
  printf("Total Number of Blocks: %u\n", sb->nzones);
  printf("Size of Inode Bitmap (in blocks): %u\n", sb->imap_blocks);
  printf("Size of Block Bitmap (in blocks): %u\n", sb->zmap_blocks);
  printf("Size of Inode Table (in blocks): %lu\n",
         SIZE_TO_BLOCK(sb->ninodes * sizeof(inode_t)));
  printf("First Block of Inode Bitmap: %u\n", 2); // typically after superblock
  printf("First Block of Block Bitmap: %u\n", 2 + sb->imap_blocks);
  printf("First Block of Inode Table: %u\n",
         2 + sb->imap_blocks + sb->zmap_blocks);
  printf("First Data Block Index: %u\n", sb->firstdatazone);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <minix_image_file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Open the file system image
  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  // Read the superblock
  superblock_t *sb = read_superblock(fd);
  if (sb == NULL) {
    fprintf(stderr, "Error: Failed to read superblock\n");
    close(fd);
    return EXIT_FAILURE;
  }

  // Verify the magic number
  if (sb->magic != MAGIC) {
    fprintf(stderr, "Error: Not a MINIX filesystem or incorrect version "
                    "(expected 0x137f).\n");
    free(sb);
    close(fd);
    return EXIT_FAILURE;
  }

  // Display superblock information
  display_superblock_info(sb);

  // Clean up
  free(sb);
  close(fd);

  return EXIT_SUCCESS;
}
