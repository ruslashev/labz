#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

const int R = 0, W = 1, LINESIZE = 512;

typedef struct {
  char channel[33];
} msg_t;

char data[32][512] = { 0 };

void die(char const *msg) {
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[]) {
  if (argc == 1)
    die("Too few arguments!\n");
  argc -= optind;
  argv += optind;
  int fd, fdpub, fdpriv;
  unsigned i = 0, size = 0; msg_t msg;
  while (1) {
    if ((fdpub = open(argv[0], O_RDONLY)) == -1)
      die(argv[0]);
    while (read(fdpub, (char*)&msg, sizeof(msg)) > 0) {
      if ((fdpriv = open(msg.channel, O_RDONLY)) == -1)
        die(msg.channel);
      pid_t pid = fork();
      int fd[2];
      if (pipe(fd) == -1)
        die("error creating fifo-channel");
      if (pid == -1)
        die("error at fork().");
      else if (pid == 0) { // child
        close(fd[W]);
        if (dup2(fd[R], fileno(stdin)) == -1)
          die("error redirecting input");
        close(fd[R]);
        if (execl("flipp", "flipp", NULL) == -1)
          die("error at execl");
      } else {
        close(fd[R]);
        if (dup2(fd[W], fileno(stdout)) == -1)
          die("error redirecting stdout");
        close(fd[W]);
        int w = 0;
        char line[LINESIZE];
        while ((w = read(fdpriv, line, LINESIZE)) > 0)
          printf("%s", line);
      }
      close (fdpriv);}
    close (fdpub);
  }
  return 0;
}

