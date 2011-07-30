#ifndef VECTOR_H
#define VECTOR_H

/* A C implementation of a vector, or dynamically expanding array. */

#include <stdlib.h>

#define BASE_CAP 10
#define EXPAND_RATIO 1.5

typedef struct{
	void** data;
	int * sizes;
	size_t length;
	size_t capacity;
} vector;

/* Create a vector object. It must be eventually destroyed by a call to 
   destroy_vector to avoid memory leaks. */
vector* create_vector();
/* Create a new vector that is composed of the items in the old vector with
   indices in the range of [start,end) */
vector* subvector(vector * vec, int start, int end);
/* Add an item to the end of the vector */
void vector_add(vector* vec, void* data, size_t n);
/* Get the item at index i of the vector */
void* vector_get(vector* vec, size_t i);
/* Set the item at index i of the vector to the data provided. */
int vector_set(vector* vec, size_t i, void* data, size_t n);
/* Insert the data at index i of the vector and shift the other 
   items to the right. */
int vector_insert(vector* vec, size_t i, void* data, size_t n);
/* Get the index of the item in the vector that is equal to the data. 
   Equality is defined as having the same bytes in memory. */
int vector_index(vector* vec, void* data, size_t n);
/* Remove the item at index i of the vector and free its memory */
void vector_remove(vector* vec, size_t i);
/* Check to make sure there is still room in the vector and expand it if 
   necessary. This function is not meant to be called directly. */
void check_length(vector* vec);
/* Destroy the vector and free all the memory associated with it. */
void destroy_vector(vector* vec);


#endif
