#include "heap.h"
#include <stdio.h>

int cmpfunc(vector * heap, int i, int j){
	int * iVal;
	int * jVal;
	
	iVal = (int*)vector_get(heap, i);
	jVal = (int*)vector_get(heap, j);
	
	return (*iVal) - (*jVal);
}

void print_heap(vector * heap){
	int i;
	int * iVal;
	
	for(i=0; i<heap->length; i++){
		iVal = (int*)vector_get(heap, i);
		printf("%d, ", *iVal);
	}
	
	printf("\n");
}

int main(void){
	vector * heap = create_vector();
	int i;
	int * iVal;
	
	for(i=0; i<8; i++){
		vector_add(heap, &i, sizeof(int));
	}
	
	build_heap(heap, cmpfunc);
	
	for(i=8; i<10; i++){
		heap_insert(heap, &i, sizeof(int), cmpfunc);
	}
	
	heap_remove(heap, cmpfunc);
	
	print_heap(heap);
	
	destroy_vector(heap);
	
	return 0;
}
