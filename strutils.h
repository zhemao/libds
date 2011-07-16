#include <stdio.h>
#include "vector.h"

typedef struct {
	char * str;
	int length;
	int capacity;
} stringbuf;

stringbuf * make_buffer(int capacity);
void buffer_concat(stringbuf * buf, char * str);
void buffer_write(stringbuf * buf, char * str);
void realloc_if_needed(stringbuf * buf);
void destroy_buffer(stringbuf * buf);
char * saferead(FILE * f);
vector* str_split(char * str, char * delim);

