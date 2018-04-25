#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

const int R = 0, W = 1;

void die(char const *msg) {
  perror(msg);
  exit(1);
}

int main(int argc, char **argv) {
  int p[2], q[2];
  if (pipe(p) == -1)
    die("error creating channel p");
  if (pipe(q) == -1)
    die("error creating channel q");
  pid_t pid = fork();
  if (pid == -1) // error
    die("fork(): failed to create child");
  else if (pid == 0) { // child
    close(p[W]);
    close(q[R]);
    if (dup2(p[R], fileno(stdin)) == -1)
      die("can't reassign stdin");
    close(p[R]);
    if (dup2(q[W], fileno(stdout)) == -1)
      die("can't reassign stdout");
    close(q[W]);
    if (execl("table", "table", "", NULL) == -1)
      die("error executing process");
  } else { // parent
    FILE *fp = fdopen(p[W], "w");
    if (!fp)
      die("can't open output file");
    close(p[R]);
    close(q[W]);
    int ch;
    while ((ch = getchar()) != EOF)
      putc(ch, fp);
    fclose(fp);
    int status;
    if (waitpid(pid, &status, 0) == -1)
      die("error waiting for child process");
    if (dup2(q[R], fileno(stdin)) == -1)
      die("can't reassign stdin");
    close(q[R]);
    while ((ch = getchar()) != EOF)
      putchar(ch);
  }
  return EXIT_SUCCESS;
}

