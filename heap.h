#ifndef __HEAP_H__
#define __HEAP_H__

#include "vector.h"

#define PARENT(i) (i-1)/2
#define LEFT(i) 2*i+1
#define RIGHT(i) 2*i+2

typedef int (*heapcmpfunc)(vector*, int, int);

void heapify(vector * heap, int i, heapcmpfunc cmpfunc);
void build_heap(vector * heap, heapcmpfunc cmpfunc);
void heap_remove(vector * heap, heapcmpfunc cmpfunc);
void heap_insert(vector * heap, void * val, int size, heapcmpfunc cmpfunc);

#endif /* __HEAP_H__ */

