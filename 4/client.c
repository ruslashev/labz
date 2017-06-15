#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

typedef struct {
  char channel[33];
} msg_t;

void die(char const *msg) {
  perror(msg);
  exit(1);
}

int main (int argc, char** argv) {
  if (!argc)
    die("too few arguments");
  argc -= optind;
  argv += optind;
  int fdpub = 0, fdpriv = 0;
  msg_t msg;
  char line[512] = { 0 };
  sprintf(msg.channel, "Fifo_%d", getpid());
  if (mkfifo(msg.channel, S_IFIFO | 0666) == -1)
    die(msg.channel);
  if ((fdpub = open(argv[0], O_WRONLY)) == -1)
    die(argv[0]);
  int w = write(fdpub, (char*)&msg, sizeof(msg));
  if ((fdpriv = open(msg.channel, O_WRONLY)) == -1) {
    close(fdpub);
    die(msg.channel);
  }
  int symb = 0;
  while ((symb = getchar()) != EOF) {
    w = dprintf(fdpriv, "%c", symb);
  }
  close(fdpriv);
  unlink(msg.channel);
  close(fdpub);
  return 0;
}

