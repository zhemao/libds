#ifndef __HEAP_H__
#define __HEAP_H__

#include "vector.h"

#define PARENT(i) (i-1)/2
#define LEFT(i) 2*i+1
#define RIGHT(i) 2*i+2

/* heapcmpfunc is the template for the comparison function used by all heap
   functions. It takes as arguments the heap itself and two integers i and j
   which represent indices of two items in the heap. If the value at i is 
   "greater" than the value at j, this function should return an integer > 0.
   If the value at i is "less" than the value at j, the function should return
   an integer < 0. If the values at i and j are equal, this function should 
   return 0 */
typedef int (*heapcmpfunc)(vector*, int, int);

/* maintain the heap property starting at index i */
void heapify(vector * heap, int i, heapcmpfunc cmpfunc);
/* build the heap */
void build_heap(vector * heap, heapcmpfunc cmpfunc);
/* removes the first element from the heap and then adjusts to maintain the 
   heap property */
void heap_remove(vector * heap, heapcmpfunc cmpfunc);
/* inserts the value into the heap such that the heap property is maintained */
void heap_insert(vector * heap, void * val, int size, heapcmpfunc cmpfunc);

#endif /* __HEAP_H__ */

