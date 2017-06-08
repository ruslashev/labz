#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define R 0
#define W 1

void error(char const *message) {
	puts(message);
	exit(1);
}

int main(int argc, char const *argv[]) {
	unsigned int indent_size = 4;
	int p[2], q[2];
	if (pipe(p) == -1)
		error("Error creating channel p");
	if (pipe(q) == -1)
		error("Error creating channel q");
	pid_t pid = fork();
	if (pid == -1) {
		error("Error at fork()");
	} else if (!pid) {
		close(p[W]);
		close(q[R]);
		if (dup2(p[R], fileno(stdin)) == -1)
			error("Can't reassign stdin #1");
		close(p[R]);
		if (dup2(q[W], fileno(stdout)) == -1)
			error("Can't reassign stdout #1");
		close(q[W]);
		if (execl("filter", "filter", "", NULL) == -1)
			error("Error calling filter");
	} else {
		FILE *fp = fdopen(p[W], "w");
		if (!fp)
			error("Error: can't open output file");
		close(p[R]);
		close(q[W]);
		int c;
		while((c = getchar()) != EOF)
			putc(c, fp);
		fclose(fp);
		int pid_status;
		if (waitpid(pid, &pid_status, 0) == -1)
			error("Error while waiting for child process");
		if (dup2(q[R], fileno(stdin)) == -1)
			error("Can't reassign stdin #2");
		close(q[R]);
		while((c = getchar()) != EOF)
			putchar(c);
	}
	return EXIT_SUCCESS;
}

