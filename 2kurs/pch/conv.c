#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#define R 0
#define W 1

void exit_with_error(char const *message) {
  puts(message);
  exit(1);
}

int main(int argc, char const *argv[]) {
  unsigned int indent_size = 4;
  int p[2], q[2]; // for fifo channels
  char arg_key;
  while ((arg_key = getopt(argc, (char * const*) argv, "hn:")) != EOF) {
    if (arg_key == 'h') {
      return EXIT_SUCCESS;
    } else if (arg_key == 'n') {
      indent_size = (unsigned int) atoi(optarg);
    } else {
      exit_with_error("Unknown key");
    }
  }
  /* skip used params */
  argc -= optind;
  argv += optind;
  if (pipe(p) == -1) /* create fifo channel */ {
    exit_with_error("Error while creating fifo channel #p");
  }
  if (pipe(q) == -1) {
    exit_with_error("Error while creating fifo channel #q");
  }
  pid_t pid = fork(); // clone process
  if (pid == -1) {
    exit_with_error("Error while fork()");
  } else if (!pid) /* if this process is a child */ {
    close(p[W]);
    close(q[R]);
    if (dup2(p[R], fileno(stdin)) == -1) /* reassign stdin */ {
      exit_with_error("Can't reassign stdin #1");
    }
    close(p[R]);
    if (dup2(q[W], fileno(stdout)) == -1) /* reassign stdout */ {
      exit_with_error("Can't reassign stdout #1");
    }
    close(q[W]);
    /* run count */
    char params[32];
    sprintf(params, "%d", indent_size);
    if (execl("filter", "filter", params, NULL) == -1) {
      exit_with_error("Error while call filter");
    }
  } else /* if this process is a parent */ {
    FILE *fp = fdopen(p[W], "w");
    if (!fp) {
      exit_with_error("Error: Can't open output file.");
    }
    close(p[R]);
    close(q[W]);
    int c;
    while((c = getchar()) != EOF) {
      putc(c, fp); // sent file to filter
    }
    fclose(fp); /* to add EOF */
    // wait for child process end it's job
    int pid_status;
    if (waitpid(pid, &pid_status, 0) == -1) {
      exit_with_error("Error while waiting child processes");
    }
    // read from child output
    if (dup2(q[R], fileno(stdin)) == -1) /* reassign stdin */ {
      exit_with_error("Can't reassign stdin #2");
    }
    close(q[R]);
    while((c = getchar()) != EOF) {
      putchar(c); // sent to output
    }
  }
  return EXIT_SUCCESS;
}

