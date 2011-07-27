#ifndef __STRUTILS_H__
#define __STRUTILS_H__

#include <stdio.h>
#include "vector.h"

typedef struct {
	char * str;
	int length;
	int capacity;
} stringbuf;

/* makes a string buffer with the given initial capacity */
stringbuf * make_buffer(int capacity);
/* concatenate the string str into the string buffer, expanding the buffer
   if necessary */
void buffer_concat(stringbuf * buf, char * str);
/* writes the characters in str, followed by a NULL character, into the buffer,
   expanding the buffer if necessary */
void buffer_write(stringbuf * buf, char * str);
/* reallocate the buffer's internal string if the length of the string exceeds
   its capacity */
void realloc_if_needed(stringbuf * buf);
/* free the buffer and its internal string */
void destroy_buffer(stringbuf * buf);
/* safely read the entire contents of the file into a properly sized string */
char * saferead(FILE * f);
/* split the string into a vector around the delimiter string */
vector* str_split(char * str, char * delim);
/* strip trailing whitespace and newline characters from a string */
void str_strip(char * str, int len);
/* convert the characters in a string to lowercase */
void str_lower(char * str);
/* convert the characters in the string to uppercase */
void str_upper(char * str);

#endif /* __STRUTILS_H__ */


