#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void exit_with_error(char const *message) {
  puts(message);
  exit(1);
}

int main(int argc, char const *argv[]) {
  char reverse = 0;
  /* handle named params */
  char arg_key;
  while ((arg_key = getopt(argc, (char * const*) argv, "hr")) != EOF) {
    if (arg_key == 'h') {
      return EXIT_SUCCESS;
    } else if (arg_key == 'r') {
      reverse = 1;
    } else {
      exit_with_error("Unknown key");
    }
  }
  argc -= optind;
  argv += optind;
  int c;
  while ((c = getchar()) != EOF) /*осуществление */ {
    if (!reverse && (c == 'i' || c == 'I')) {
      putchar('1');
    } else if (!reverse && (c == 'o' || c == 'O')) {
      putchar('0');
    } else if (reverse && c == '0') {
      putchar('o');
    } else if (reverse && c == '1') {
      putchar('i');
    } else if (reverse && c == '2') {
      printf("to");
    } else if (reverse && c == '3') {
      printf("fri");
    } else if (reverse && c == '4') {
      printf("for");
    } else {
      putchar(c);
    }
  }
  return EXIT_SUCCESS;
}

