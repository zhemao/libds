#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "strutils.h"

char * saferead(FILE * f){
	int len;
	char * buf;
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);
	buf = (char*)malloc(sizeof(char)*(len+1));
	fread(buf, sizeof(char), len, f);
	buf[len] = '\0';
	return buf;
}

char * str_join(char **args, char * sep, int len){
	int i;
	int size;
	char * str;
	int seplen = strlen(sep);
	
	if(len==0) return NULL;
	
	size = (len-1) * seplen;
	for(i=0; i<len; i++){
		size+=strlen(args[i]);
	}
	
	if(size==0) return NULL;
	
	str = (char*)malloc(sizeof(char)*(size+1));
	strcpy(str, args[0]);
	
	for(i=1; i<len; i++){
		strcat(str, sep);
		strcat(str, args[i]);
	}
	return str;
}

char ** str_split(char * str, char * delim, int * size){
	int len = 0, cap = 10;
	int slen;
	char ** array = (char**)calloc(sizeof(char*), cap);
	
	char * tok = strtok(str, delim);
	while(tok){
		if(len >= cap){
			cap = len * 1.5;
			array = (char**)realloc(array, sizeof(char*) * cap);
		}
		slen = strlen(tok);
		if(slen > 0){
			array[len] = (char*)malloc(slen+1);
			strncpy(array[len], tok, slen);
			array[len][slen] = 0;
			len++;
		}
		tok = strtok(NULL, delim);
	}
	
	*size = len;
	return array;
}

void free_str_array(char ** arr, int len){
	int i;
	for(i=0; i<len; i++){
		free(arr[i]);
	}
	free(arr);
}

stringbuf * make_buffer(int capacity){
	stringbuf * buf = (stringbuf*)malloc(sizeof(stringbuf));
	buf->length = 0;
	buf->capacity = capacity;
	buf->str = (char*)malloc(sizeof(char)*capacity);
	memset(buf->str, 0, capacity);
	return buf;
}

void buffer_write(stringbuf * buf, char * str){
	int len = strlen(str);
	buf->length = len;
	realloc_if_needed(buf);
	strcpy(buf->str, str);
}

void buffer_nwrite(stringbuf * buf, char * str, int n){
	buf->length = n;
	realloc_if_needed(buf);
	strncpy(buf->str, str, n);
	buf->str[n] = '\0';
}

void buffer_concat(stringbuf * buf, char * str){
	int len = strlen(str);
	buf->length += len;
	realloc_if_needed(buf);
	strcat(buf->str, str);
}

void buffer_nconcat(stringbuf * buf, char * str, int len){
	buf->length += len;
	realloc_if_needed(buf);
	strncat(buf->str, str, len);
	buf->str[buf->length] = 0;
}

void realloc_if_needed(stringbuf * buf){
	if(buf->capacity <= buf->length){
		buf->capacity = buf->length * 1.25;
		buf->str = realloc(buf->str, buf->capacity);
	}
}

void destroy_buffer(stringbuf * buf){
	free(buf->str);
	free(buf);
}

void str_strip(char * str, int len){
	int i;
	char c;
	for(i=len-1; i>=0; i--){
		c = str[i];
		if(c=='\n'||c=='\r'||c=='\t'||c==' ')
			str[i] = 0;
		else break;
	}
}

void str_lower(char * str){
	int i;
	for(i=0; str[i]; i++){
		if(isupper(str[i])){
			str[i] += 32;
		}
	}
}

void str_upper(char * str){
	int i;
	for(i=0; str[i]; i++){
		if(islower(str[i])){
			str[i] -= 32;
		}
	}
}

int str_startswith(char * stra, char * strb){
	int len = strlen(strb);
	return strncmp(stra, strb, len) == 0;
}

int str_endswith(char * stra, char * strb){
	int lena = strlen(stra);
	int lenb = strlen(strb);
	
	if(lenb > lena) return 0;
	
	return strcmp(stra+(lena-lenb), strb)==0;
}
