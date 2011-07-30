#include "strutils.h"
#include "vector.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	char str[256];
	stringbuf * buf;
	char * joinstr;
	vector * vec;
	FILE * f;
	int nb;
	if(argc < 2){
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}
	f = fopen(argv[1], "r");
	buf = make_buffer(256);
	while(nb = fread(str, sizeof(char), 255, f)){
		str[nb] = '\0';
		buffer_concat(buf, str);
	}
	printf("%s", buf->str);
	
	vec = str_split(buf->str, " ");
	joinstr = str_join((char**)vec->data, " ", vec->length);
	
	printf("%s", joinstr);
	
	if(strcmp(joinstr, buf->str)==0){
		printf("success!\n");
	} else{
		printf("failure\n");
	}
	
	free(joinstr);	
	destroy_vector(vec);
	destroy_buffer(buf);
	fclose(f);
	return 0;
}
