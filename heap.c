#include "heap.h"
#include <stdlib.h>
#include <string.h>

heap_p create_heap(heapcmpfunc cmpfunc){
	heap_p hp = (heap_p) malloc(sizeof(struct heap));
	hp->vec = create_vector();
	hp->cmpfunc = cmpfunc;

	return hp;
}

void destroy_heap(heap_p hp){
	destroy_vector(hp->vec);
	free(hp);
}

void heapify(heap_p hp, int i){
	int largest;
	int l = LEFT(i);
	int r = RIGHT(i);
	
	if(l < hp->vec->length && hp->cmpfunc(hp->vec, l, i) > 0)
		largest = l;
	else largest = i;
	
	if(r < hp->vec->length && hp->cmpfunc(hp->vec, r, largest) > 0)
		largest = r;
		
	if(largest != i){
		vector_swap(hp->vec, i, largest);
		heapify(hp, largest);
	}
}

void build_heap(heap_p hp){
	int i;
	
	for(i=PARENT(hp->vec->length-1); i>=0; i--){
		heapify(hp, i);
	}
}

void heap_remove(heap_p hp){
	
	vector_swap(hp->vec, 0, hp->vec->length-1);
	vector_remove(hp->vec, hp->vec->length-1);
	
	heapify(hp, 0);
}

void heap_insert(heap_p hp, void * val, int size){
	int i;
	
	vector_add(hp->vec, val, size);
	
	for(i=hp->vec->length-1; i>0; i=PARENT(i)){
		if(hp->cmpfunc(hp->vec, PARENT(i), i) > 0)
			break;
		vector_swap(hp->vec, PARENT(i), i);
	}
}
