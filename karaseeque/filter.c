#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define WORD_LEN_MAX 4096

typedef struct char_row {
	char **data;
	int len;
	int i;
} char_row;

void char_row_create(char_row *r) {
	r->len = 1;
	r->data = malloc(r->len * sizeof(char*));
	r->i = 0;
	memset(r->data, 0, r->len);
}

void char_row_expand(char_row *r, int nlen) {
	while (nlen > r->len) {
		r->len = (r->len + 1) * 2;
		r->data = realloc(r->data, r->len * sizeof(char*));
		if (!r->data)
			abort();
	}
}

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a < b ? a : b;
}

void char_row_insert(char_row *r, const char *s) {
	if (r->i + 1 >= r->len)
		char_row_expand(r, r->i + 1);
	r->data[r->i] = malloc((strlen(s) + 1) * sizeof(char));
	r->data[r->i][strlen(s)] = 0;
	strncpy(r->data[r->i++], s, strlen(s));
}

int char_row_max_len(char_row *r) {
	int max_len = 0;
	for (int i = 0; i < r->i; ++i)
		max_len = max(strlen(r->data[i]), max_len);
	return max_len;
}

void char_row_print(char_row *r, int max_len) {
	for (int i = 0; i < r->i; ++i)
		printf("%-*s ", max_len, r->data[i]);
	printf("\n");
}

typedef struct column {
	char_row *data;
	struct column *next;
} column;

void column_print(column *head) {
	int all_max_len = 0;
	column *ptr = head;
	while (ptr != NULL) {
		all_max_len = max(all_max_len, char_row_max_len(ptr->data));
		ptr = ptr->next;
	}
	ptr = head;
	while (ptr != NULL) {
		char_row_print(ptr->data, all_max_len);
		ptr = ptr->next;
	}
}

column* column_insert(column *head, char_row *data) {
	column *c = malloc(sizeof(struct column));
	c->next = NULL;
	c->data = data;
	if (head == NULL)
		return c;
	column *ptr = head;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = c;
	return head;
}

void column_free(column *head) {
	column *ptr = head;
	while (ptr != NULL) {
		column *t = ptr;
		ptr = ptr->next;
		for (int i = 0; i < t->data->i; ++i)
			free(t->data->data[i]);
		free(t->data->data);
		free(t->data);
	}
	free(head);
}

int main() {
	column *c = NULL;
	char *line = NULL;
	size_t length = 0;
	ssize_t n;

	while ((n = getline(&line, &length, stdin)) >= 0) {
		char *p = line;
		char_row *r = malloc(sizeof(char_row));
		char_row_create(r);
		char word_buf[WORD_LEN_MAX];
		int w = 0;
		do {
			if (*p != ' ' && *p != '\n')
				word_buf[w++] = *p;
			else {
				word_buf[w++] = 0;
				char_row_insert(r, word_buf);
				w = 0;
			}
		} while (*p++);
		c = column_insert(c, r);
	}

	column_print(c);
	column_free(c);
	free(line);
}

