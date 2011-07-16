#include "strutils.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	char str[256];
	stringbuf * buf;
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
	destroy_buffer(buf);
	fclose(f);
	return 0;
}
