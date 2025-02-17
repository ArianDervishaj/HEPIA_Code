#include <assert.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

struct stat info;

// Function to print permissions
void print_permission(__mode_t mode) {
  char string[10];
  string[0] = (S_ISDIR(mode))   ? 'd'
              : (S_ISLNK(mode)) ? 'l'
                                : '-';
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

// Function to print time
void print_time(time_t time) {
  char time_last_change[1000];
  struct tm *timeinfo = localtime(&time);
  strftime(time_last_change, 1000, "%c", timeinfo);
  printf("%s\t", time_last_change);
}

// Function to print file size
void print_file_size(off_t size) { printf("%ld\t", size); }

// Function to print information of a file
int file_infos(char *path) {
  if (path == NULL) {
    perror("Path == NULL");
    return EXIT_FAILURE;
  }

  if (lstat(path, &info) == -1) { 
    perror("lstat");
    return EXIT_FAILURE;
  }

  print_permission(info.st_mode);
  print_file_size(info.st_size);
  print_time(info.st_mtim.tv_sec);

  if (S_ISLNK(info.st_mode)) {
    char link_target[1024];
    ssize_t len = readlink(path, link_target, sizeof(link_target) - 1);
    if (len != -1) {
      link_target[len] = '\0';
      printf("%s -> %s\n", path, link_target);
    } else {
      perror("readlink");
      return EXIT_FAILURE;
    }
  } else {
    printf("%s\n", path);
  }

  return EXIT_SUCCESS;
}

// Recursive function to list the contents of a directory
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

    if (lstat(fullpath, &info) == -1) {
      perror("lstat");
      continue;
    }

    file_infos(fullpath);

    if (S_ISDIR(info.st_mode)) {
      list_directory(fullpath);
    }
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

  if (lstat(path, &info) == -1) {
    perror("lstat");
    return EXIT_FAILURE;
  }

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
