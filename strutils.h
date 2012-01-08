#ifndef __LIBDS_STRUTILS_H__
#define __LIBDS_STRUTILS_H__

#include <stdio.h>

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
/* concatenate n characters of string str in the buffer, expanding the buffer
   if necessary */
void buffer_nconcat(stringbuf * buf, char * str, int n);
/* writes the characters in str into the buffer, 
   expanding the buffer if necessary */
void buffer_write(stringbuf * buf, char * str);
/* writes n characters from str into the buffer, expanding the buffer if 
   necessary */
void buffer_nwrite(stringbuf * buf, char * str, int n);
/* reallocate the buffer's internal string if the length of the string exceeds
   its capacity */
void realloc_if_needed(stringbuf * buf);
/* free the buffer and its internal string */
void destroy_buffer(stringbuf * buf);
/* safely read the entire contents of the file into a properly sized string */
char * saferead(FILE * f);
/* join an array of strings of length len with separator sep */
char* str_join(char **args, char * sep, int len);
/* split the string into a vector around the delimiter string */
char ** str_split(char * str, char * delim, int * size);
/* free the elements of a string array, as well as the array itself */
void free_str_array(char ** arr, int len);
/* strip trailing whitespace and newline characters from a string */
void str_strip(char * str, int len);
/* convert the characters in a string to lowercase */
void str_lower(char * str);
/* convert the characters in the string to uppercase */
void str_upper(char * str);
/* tests whether stra is starts with the string strb */
int str_startswith(char * stra, char * strb);
/* tests whether stra ends with the string strb */
int str_endswith(char * stra, char * strb);
#endif /* __STRUTILS_H__ */


