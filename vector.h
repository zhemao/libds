#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#define BASE_CAP 10
#define EXPAND_RATIO 1.5

typedef struct{
	void** data;
	size_t length;
	size_t capacity;
} vector;

vector* create_vector();
void vector_add(vector* vec, void* data, size_t n);
void* vector_get(vector* vec, size_t i);
int vector_set(vector* vec, size_t i, void* data, size_t n);
int vector_insert(vector* vec, size_t i, void* data, size_t n);
void vector_remove(vector* vec, size_t i);
void check_length(vector* vec);
void destroy_vector(vector* vec);
int vector_index(vector* vec, void* data, size_t n);

#endif
