#include "heap.h"
#include <stdio.h>

int cmpfunc(vector_p heap, int i, int j){
	int * iVal;
	int * jVal;
	
	iVal = (int*)vector_get(heap, i);
	jVal = (int*)vector_get(heap, j);
	
	return (*iVal) - (*jVal);
}

void print_heap(vector_p heap){
	int i;
	int * iVal;
	
	for(i=0; i<heap->length; i++){
		iVal = (int*)vector_get(heap, i);
		printf("%d, ", *iVal);
	}
	
	printf("\n");
}

int main(void){
	heap_p hp = create_heap(cmpfunc);
	int i;
	
	for(i=0; i<8; i++){
		vector_add(hp->vec, &i, sizeof(int));
	}
	
	build_heap(hp);

    print_heap(hp->vec);
	
	for(i=8; i<10; i++){
		heap_insert(hp, &i, sizeof(int));
	}

    print_heap(hp->vec);
	
	heap_remove(hp);
	
	print_heap(hp->vec);
	
	destroy_heap(hp);
	
	return 0;
}
