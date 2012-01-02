#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

int main(void){
	vector_p vec = create_vector();
	vector_p subvec;
	int x;
	char *str = "hello, world";
	char *str2 = "goodbye, world";
	for(x=0;x<15;x++){
		vector_add(vec, (void*)str, strlen(str)+1);
	}
	vector_insert(vec, 4, (void*) str2, strlen(str2)+1);
	vector_set(vec, 7, (void*) str2, strlen(str2)+1);
	vector_remove(vec, 4);
	printf("%d\n", (int)vec->length);
	
	subvec = subvector(vec, 1, 5);
	
	for(x=0;x<vec->length;x++){
		printf("%s\n", (char*)vector_get(vec, x));
	}
	
	printf("\n");
	
	for(x=0;x<subvec->length;x++){
		printf("%s\n", (char*)vector_get(subvec, x));
	}
	destroy_vector(vec);
	destroy_vector(subvec);
	return 0;
}
