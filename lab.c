#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

void usage(const char *name) {
  printf("usage: %s [dir]\n", name);
  exit(EXIT_FAILURE);
}

struct direntry {
  char name[512];
};

int main(int argc, char **argv) {
  if (argc >= 3)
    usage(argv[0]);

  char dir[512] = ".";
  if (argc == 2)
    strncpy(dir, argv[1], 80);

  DIR *dp = opendir(dir);
  if (dp == NULL) {
    char errmsg[512];
    snprintf(errmsg, 80, "cannot access '%s'", dir);
    perror(errmsg);
    exit(EXIT_FAILURE);
  }

  struct dirent *file;
  while (file = readdir(dp)) {
    char buf[512];
    struct stat file_stat;
    snprintf(buf, 512, "%s/%s", dir, file->d_name);
    stat(buf, &file_stat);
    printf("%zu %s\n", file_stat.st_size, file->d_name);
  }

  exit(0);
}

