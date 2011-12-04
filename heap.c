#include "heap.h"
#include <stdlib.h>
#include <string.h>

void heapify(vector * heap, int i, heapcmpfunc cmpfunc){
	int largest;
	int l = LEFT(i);
	int r = RIGHT(i);
	
	void *ival, *lval, *rval, *largeval;
	
	if(l < heap->length && cmpfunc(heap, l, i) > 0)
		largest = l;
	else largest = i;
	
	if(r < heap->length && cmpfunc(heap, r, largest) > 0)
		largest = r;
		
	if(largest != i){
		vector_swap(heap, i, largest);
		heapify(heap, largest, cmpfunc);
	}
}

void build_heap(vector * heap, heapcmpfunc cmpfunc){
	int i;
	
	for(i=PARENT(heap->length-1); i>=0; i--){
		heapify(heap, i, cmpfunc);
	}
}

void heap_remove(vector * heap, heapcmpfunc cmpfunc){
	
	vector_swap(heap, 0, heap->length-1);
	vector_remove(heap, heap->length-1);
	
	heapify(heap, 0, cmpfunc);
}

void heap_insert(vector * heap, void * val, int size, heapcmpfunc cmpfunc){
	int i;
	
	vector_add(heap, val, size);
	
	for(i=heap->length-1; i>0; i=PARENT(i)){
		if(cmpfunc(heap, PARENT(i), i) > 0)
			break;
		vector_swap(heap, PARENT(i), i);
	}
}
