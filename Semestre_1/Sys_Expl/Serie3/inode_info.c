#include "minix.h"
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Function to check if a specific inode is used (1) or free (0)
int is_inode_used(uint8_t *inode_bitmap, int inode_number) {
  int byte_index = inode_number / 8;
  int bit_index = inode_number % 8;
  return (inode_bitmap[byte_index] & (1 << bit_index)) != 0;
}

// Function to display file permissions in rwx format
void display_permissions(uint16_t mode) {
  const char *perms = "rwx";
  for (int i = 8; i >= 0; i--) {
    printf("%c", (mode & (1 << i)) ? perms[i % 3] : '-');
    if (i % 3 == 0 && i != 0)
      printf(" ");
  }
}

// Function to display inode information
void display_inode_info(inode_t *inode) {
  // Display file type
  switch (INODE_EXTRACT_TYPE(inode->mode)) {
  case TYPE_FIFO:
    printf("File Type: FIFO\n");
    break;
  case TYPE_CHARDEV:
    printf("File Type: Character Device\n");
    break;
  case TYPE_DIR:
    printf("File Type: Directory\n");
    break;
  case TYPE_BLOCKDEV:
    printf("File Type: Block Device\n");
    break;
  case TYPE_FILE:
    printf("File Type: Regular File\n");
    break;
  case TYPE_SYMLINK:
    printf("File Type: Symbolic Link\n");
    break;
  default:
    printf("File Type: Unknown\n");
    break;
  }

  // Display permissions
  printf("Permissions: ");
  display_permissions(inode->mode);
  printf("\n");

  // Display UID, GID, file size, and link count
  printf("UID: %u\n", inode->uid);
  printf("GID: %u\n", inode->gid);
  printf("File Size: %u bytes\n", inode->size);
  printf("Link Count: %u\n", inode->nlinks);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <minix_image_file> <inode_number>\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char *filename = argv[1];
  int inode_number = atoi(argv[2]);

  // Open the file system image
  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  // Read the superblock
  superblock_t *sb = read_superblock(fd);
  if (!sb || sb->magic != MAGIC) {
    fprintf(stderr, "Error: Invalid MINIX file system or incorrect version.\n");
    free(sb);
    close(fd);
    return EXIT_FAILURE;
  }

  // Read inode bitmap
  uint8_t *inode_bitmap = read_inodes_bitmap(fd, sb);
  if (!inode_bitmap) {
    fprintf(stderr, "Error: Failed to read inode bitmap.\n");
    free(sb);
    close(fd);
    return EXIT_FAILURE;
  }

  // Check if the inode number is valid and used
  if (inode_number < 1 || inode_number > sb->ninodes) {
    fprintf(stderr, "Error: Inode number out of range.\n");
    free(sb);
    free(inode_bitmap);
    close(fd);
    return EXIT_FAILURE;
  }

  if (!is_inode_used(inode_bitmap, inode_number - 1)) {
    fprintf(stderr, "Error: Inode %d is not used.\n", inode_number);
    free(sb);
    free(inode_bitmap);
    close(fd);
    return EXIT_FAILURE;
  }

  // Read the inode table
  inode_t *inodes = read_inodes_table(fd, sb);
  if (!inodes) {
    fprintf(stderr, "Error: Failed to read inode table.\n");
    free(sb);
    free(inode_bitmap);
    close(fd);
    return EXIT_FAILURE;
  }

  // Display the inode information
  inode_t *inode = &inodes[inode_number - 1];
  display_inode_info(inode);

  // Clean up
  free(sb);
  free(inode_bitmap);
  free(inodes);
  close(fd);

  return EXIT_SUCCESS;
}
