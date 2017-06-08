#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define WORD_LEN_MAX 4096

typedef struct word_cont
{
	char **data;
	int len;
	int i;
} word_cont;

void word_cont_create(word_cont *r)
{
	r->len = 1;
	r->data = malloc(r->len * sizeof(char*));
	r->i = 0;
	memset(r->data, 0, r->len);
}

void word_cont_expand(word_cont *r, int nlen)
{
	while (nlen > r->len)
	{
		r->len = (r->len + 1) * 2;
		r->data = realloc(r->data, r->len * sizeof(char*));
		if (!r->data)
			abort();
	}
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int min(int a, int b)
{
	return a < b ? a : b;
}

void word_cont_insert(word_cont *r, const char *s)
{
	if (r->i + 1 >= r->len)
		word_cont_expand(r, r->i + 1);
	r->data[r->i] = malloc((strlen(s) + 1) * sizeof(char));
	r->data[r->i][strlen(s)] = 0;
	strncpy(r->data[r->i++], s, strlen(s));
}

int word_cont_max_len(word_cont *r)
{
	int max_len = 0;
	for (int i = 0; i < r->i; ++i)
		max_len = max(strlen(r->data[i]), max_len);
	return max_len;
}

void word_cont_print(word_cont *r, int max_len)
{
	for (int i = 0; i < r->i; ++i)
		printf("%-*s ", max_len, r->data[i]);
	printf("\n");
}

typedef struct main_cont
{
	word_cont *data;
	struct main_cont *next;
} main_cont;

void main_cont_print(main_cont *head)
{
	int all_max_len = 0;
	main_cont *ptr = head;
	while (ptr != NULL)
	{
		all_max_len = max(all_max_len, word_cont_max_len(ptr->data));
		ptr = ptr->next;
	}
	ptr = head;
	while (ptr != NULL)
	{
		word_cont_print(ptr->data, all_max_len);
		ptr = ptr->next;
	}
}

main_cont* main_cont_insert(main_cont *head, word_cont *data)
{
	main_cont *c = malloc(sizeof(struct main_cont));
	c->next = NULL;
	c->data = data;
	if (head == NULL)
		return c;
	main_cont *ptr = head;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = c;
	return head;
}

void main_cont_free(main_cont *head)
{
	main_cont *ptr = head;
	while (ptr != NULL)
	{
		main_cont *t = ptr;
		ptr = ptr->next;
		for (int i = 0; i < t->data->i; ++i)
			free(t->data->data[i]);
		free(t->data->data);
		free(t->data);
	}
	free(head);
}

int main()
{
	main_cont *c = NULL;
	char *line = NULL;
	size_t length = 0;
	ssize_t n;

	while ((n = getline(&line, &length, stdin)) >= 0)
	{
		char *p = line;
		word_cont *r = malloc(sizeof(word_cont));
		word_cont_create(r);
		char word_buf[WORD_LEN_MAX];
		int w = 0;
		do
		{
			if (*p != ' ' && *p != '\n')
				word_buf[w++] = *p;
			else
			{
				word_buf[w++] = 0;
				word_cont_insert(r, word_buf);
				w = 0;
			}
		} while (*p++);
		c = main_cont_insert(c, r);
	}

	main_cont_print(c);
	main_cont_free(c);
	free(line);
}

