#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(void){
	vector* vec = create_vector();
	int x;
	char *str = "hello, world";
	char *str2 = "goodbye, world";
	for(x=0;x<15;x++){
		vector_add(vec, (void*)str);
	}
	vector_insert(vec, 4, (void*) str2);
	vector_set(vec, 7, (void*) str2);
	vector_remove(vec, 4);
	printf("%d\n", (int)vec->length);
	for(x=0;x<vec->length;x++){
		printf("%s\n", (char*)vector_get(vec, x));
	}
	destroy_vector(vec);
	return 0;
}
