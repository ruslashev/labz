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
			putchar(toupper(*p));
		} while (*p++);
	}

	free(line);
}

