#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sysexits.h>
#include <time.h>
#include <unistd.h>

static char* g_dir = ".";

static void print_permissions(mode_t mode) {
  putchar((mode & S_IRUSR) ? 'r' : '-');
  putchar((mode & S_IWUSR) ? 'w' : '-');
  putchar((mode & S_IXUSR) ? 'x' : '-');
  putchar((mode & S_IRGRP) ? 'r' : '-');
  putchar((mode & S_IWGRP) ? 'w' : '-');
  putchar((mode & S_IXGRP) ? 'x' : '-');
  putchar((mode & S_IROTH) ? 'r' : '-');
  putchar((mode & S_IWOTH) ? 'w' : '-');
  putchar((mode & S_IXOTH) ? 'x' : '-');
}

static void print_filetype(mode_t mode) {
  switch (mode & S_IFMT) {
    case S_IFREG:  putchar('-'); break;
    case S_IFDIR:  putchar('d'); break;
    case S_IFLNK:  putchar('l'); break;
    case S_IFCHR:  putchar('c'); break;
    case S_IFBLK:  putchar('b'); break;
    case S_IFSOCK: putchar('s'); break;
    case S_IFIFO:  putchar('f'); break;
  }
}

static void print_time(time_t mod_time) {
  time_t curr_time;
  time(&curr_time);
  struct tm *t = localtime(&curr_time);
  const int curr_mon = t->tm_mon, curr_yr = 1970 + t->tm_year;

  t = localtime(&mod_time);
  const int mod_mon = t->tm_mon, mod_yr = 1970 + t->tm_year;

  char time_buf[256];
  const char* format = ((mod_yr == curr_yr) && (mod_mon >= (curr_mon - 6)))
    ? "%b %e %H:%M" : "%b %e %Y";
  strftime(time_buf, sizeof(time_buf), format, t);
  printf("%s", time_buf);
}

static struct stat get_stats(const char *dir, const char *filename) {
  char path[1024];
  snprintf(path, sizeof(path), "%s/%s", dir, filename);
  struct stat sb;
  if (lstat(path, &sb) < 0) {
    perror(path);
    exit(EX_IOERR);
  }
  return sb;
}

static bool is_dir(const char *dir, const char *filename) {
  return get_stats(dir, filename).st_mode & S_IFDIR;
}

static bool is_exec(mode_t mode) {
  return (mode & S_IXUSR) || (mode & S_IXGRP) || (mode & S_IXOTH);
}

static bool is_in_dir(const char *dir, const char *filename) {
  DIR* dfd = opendir(dir);
  if (!dfd) {
    perror(dir);
    return false;
  }
  struct dirent* dp = readdir(dfd);
  while (dp) {
    if (strcmp(filename, dp->d_name) == 0) {
      closedir(dfd);
      return true;
    }
    dp = readdir(dfd);
  }
  fprintf(stderr, "file \'%s\' not found\n", filename);
  closedir(dfd);
  return false;
}

static void print_name_or_link(const char *dir, const char *filename
    , mode_t mode) {
  if (mode & S_IFLNK) {
    char link_buf[512];
    int count = readlink(filename, link_buf, sizeof(link_buf));
    if (count >= 0) {
      link_buf[count] = '\0';
      printf(" %s -> %s\n", filename, link_buf);
      return;
    }
  }

  printf(" %s", filename);

  if (is_dir(dir, filename))
    putchar('/');
  else if (is_exec(mode))
    putchar('*');

  putchar('\n');
}

static void display_stats(char *dir, char *filename) {
  if (!is_in_dir(dir, filename))
    return;

  g_dir = dir;

  struct stat sb = get_stats(dir, filename);

  print_filetype(sb.st_mode);
  print_permissions(sb.st_mode);
  printf("%2d %s %s %6ld ", sb.st_nlink, getpwuid(sb.st_uid)->pw_name
      , getgrgid(sb.st_gid)->gr_name, (long)sb.st_size);
  print_time(sb.st_mtime);
  print_name_or_link(dir, filename, sb.st_mode);
}

static int cmp_lex(const void *a, const void *b) {
  return strcasecmp(*(const void**)a, *(const void**)b);
}

bool can_recurse_dir(const char *dir, char *filename) {
  if (!strcmp(".", filename) || !strcmp("..", filename))
    return false;
  char path[4096];
  sprintf(path, "%s/%s", dir, filename);
  struct stat sb;
  if (lstat(path, &sb) < 0) {
    perror(path);
    exit(EX_IOERR);
  }
  return S_ISDIR(sb.st_mode);
}

int total_contents(char *dir) {
  DIR *dfd = opendir(dir);
  struct dirent *dp = readdir(dfd);
  int count = 0;
  while (dp = readdir(dfd)) {
    count += get_stats(dir, dp->d_name).st_blocks / 2;
    if (false && can_recurse_dir(dir, dp->d_name)) {
      char next[4096];
      snprintf(next, sizeof(next), "%s/%s", dir, dp->d_name);
      count += total_contents(next);
    }
  }
  closedir(dfd);
  return count;
}

static void display_dir(char *dir) {
  DIR *dfd = opendir(dir);
  struct dirent *dp = readdir(dfd);
  size_t contents_len = 4096;
  char **contents = malloc(contents_len * sizeof(char*));
  if (!contents)
    abort();

  size_t count = 0;
  while (dp) {
    while (count >= contents_len) {
      contents_len *= 2;
      contents = realloc(contents, sizeof(*contents) * contents_len);
      if (!contents)
        abort();
    }
    contents[count] = dp->d_name;
    ++count;
    dp = readdir(dfd);
  }

  g_dir = dir;
  qsort(contents, count, sizeof(char*), cmp_lex);

  printf("total %d\n", total_contents(dir));

  for (size_t i = 0; i < count; ++i)
    display_stats(dir, contents[i]);

  closedir(dfd);
  free(contents);
}

int main(int argc, char* argv[]) {
  if (argc == 1)
    display_dir(".");

  for (int i = 1; i < argc; ++i) {
    if (!is_dir(".", argv[i])) {
      display_stats(".", argv[i]);
      continue;
    }
    if (argc - 1 >= 2) {
      if (i != 1)
        printf("\n");
      printf("%s:\n", argv[i]);
    }
    display_dir(argv[i]);
  }
}

