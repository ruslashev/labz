#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
  char *line = NULL;
  size_t length = 0U;
  ssize_t n;

  while ((n = getline(&line, &length, stdin)) >= 0) {
    char *p = line;
    do {
      if (islower(*p))
        putchar(toupper(*p));
      else if (isupper(*p))
        putchar(tolower(*p));
      else
        putchar(*p);
    } while (*p++);
  }

  free(line);
}

