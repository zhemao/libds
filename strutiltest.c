#include "strutils.h"
#include "vector.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	char str[256];
	stringbuf * buf;
	char * joinstr;
	char ** array;
	int len;
	FILE * f;
	int nb;

	if(argc < 2){
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}
	f = fopen(argv[1], "r");
	buf = make_buffer(256);
	
    while((nb = fread(str, sizeof(char), 255, f)) > 0){
		str[nb] = '\0';
		buffer_concat(buf, str);
	}
	printf("%s", buf->str);
	
	array = str_split(buf->str, " ", &len);
	joinstr = str_join(array, " ", len);
	
	printf("%s", joinstr);
	
	free_str_array(array, len);

	free(joinstr);	
	destroy_buffer(buf);
	fclose(f);
	return 0;
}
