#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

// S_ISREG(m)	fichier de données ?
// S_ISDIR(m)	répertoire ?
// S_ISCHR(m)	character device ?
// S_ISBLK(m)	block device ?
// S_ISFIFO(m)	FIFO (named pipe) ?
// S_ISLNK(m)	lien symbolique ?
// S_ISSOCK(m)	socket?

// struct stat{
//   dev_t     st_dev;     //device ID
//   ino_t     st_ino;     //i-node number
//   mode_t    st_mode;    //protection and type
//   nlink_t   st_nlink;   //number of hard links
//   uid_t     st_uid;     //user ID of owner
//   gid_t     st_gid;     //group ID of owner
//   dev_t     st_rdev;    //device type (if special file)
//   off_t     st_size;    //total size, in bytes
//   blksize_t st_blksize; //blocksize for filesystem I/O
//   blkcnt_t  st_blocks;  //number of 512B blocks
//   time_t    st_atime;   //time of last access
//   time_t    st_mtime;   //time of last modification
//   time_t    st_ctime;   //time of last change
// };

struct stat info;

void print_permission(__mode_t mode) {
  char string[10];
  string[0] = '-';
  string[1] = (mode & S_IRUSR) ? 'r' : '-';
  string[2] = (mode & S_IWUSR) ? 'w' : '-';
  string[3] = (mode & S_IXUSR) ? 'x' : '-';
  string[4] = (mode & S_IRGRP) ? 'r' : '-';
  string[5] = (mode & S_IWGRP) ? 'w' : '-';
  string[6] = (mode & S_IXGRP) ? 'x' : '-';
  string[7] = (mode & S_IROTH) ? 'r' : '-';
  string[8] = (mode & S_IWOTH) ? 'w' : '-';
  string[9] = (mode & S_IXOTH) ? 'x' : '-';

  printf("%s\t", string);
}

void print_time(time_t time) {
  char time_last_change[1000];
  struct tm *timeinfo = localtime(&time);
  strftime(time_last_change, 1000, "%c", timeinfo);
  printf("%s\t", time_last_change);
}

void print_file_size(off_t size) { printf("%ld ", size); }

int file_infos(char *path) {
  if (path == NULL) {
    perror("Path == NULL");
    return EXIT_FAILURE;
  }

  if (stat(path, &info) == -1) {
    perror("stat");
    return EXIT_FAILURE;
  }

  print_permission(info.st_mode);

  print_file_size(info.st_size);

  print_time(info.st_mtim.tv_sec);

  printf("%s\n", path);

  return EXIT_SUCCESS;
}

int list_directory(const char *path) {
  DIR *dir;
  struct dirent *entry;

  if ((dir = opendir(path)) == NULL) {
    perror("opendir");
    return EXIT_FAILURE;
  }

  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    char fullpath[1024];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

    file_infos(fullpath);
  }

  closedir(dir);
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("Donner le path du fichier/dossier\n");
    return EXIT_FAILURE;
  }

  char *path = argv[1];

  if (S_ISDIR(info.st_mode)) {
    printf("C'est un répertoire\n");
    int exit_code = list_directory(path);
    if (exit_code == EXIT_FAILURE) {
      fprintf(stderr, "Failed to list directory %s\n", path);
    }
  } else {
    int exit_code = file_infos(path);
    if (exit_code == EXIT_FAILURE) {
      fprintf(stderr, "Failed to list file %s\n", path);
    }
  }

  return EXIT_SUCCESS;
}