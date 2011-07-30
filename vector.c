#include "vector.h"
#include <string.h>

vector* create_vector(){
	vector* vec = (vector*)malloc(sizeof(vector));
	vec->data = (void**)malloc(sizeof(void*)*BASE_CAP);
	vec->capacity = BASE_CAP;
	vec->length = 0;
	return vec;
}

vector * subvector(vector * old, int start, int end){
	int length = end-start;
	vector * new = create_vector();
	int i;
	void * val;
	for(i=start; i<end; i++){
		val = vector_get(old, i);
		vector_add(new, val, sizeof(val));
	}
	return new;
}

void check_length(vector* vec){
	if(vec->length >= vec->capacity){
		vec->capacity*=EXPAND_RATIO;
		vec->data = (void**)realloc((void*)vec->data, vec->capacity*sizeof(void*));
	}
}

void vector_add(vector* vec, void* data, size_t n){
	check_length(vec);
	vec->data[vec->length] = malloc(n);
	memcpy(vec->data[vec->length], data, n);
	vec->length++;
}

void* vector_get(vector* vec, size_t i){
	if(i >= vec->length)
		return NULL;
	return vec->data[i];
}

int vector_set(vector* vec, size_t i, void* data, size_t n){
	if(i >= vec->length)
		return -1;
	free(vec->data[i]);
	vec->data[i] = malloc(n);
	memcpy(vec->data[i], data, n);
	return 0;
}

int vector_insert(vector* vec, size_t i, void* data, size_t n){
	int x;
	check_length(vec);
	for(x=vec->length;x>=i;x--)
		vec->data[x+1] = vec->data[x];
	vec->data[i] = malloc(n);
	memcpy(vec->data[i], data, n);
	vec->length++;
	return 0;
}

void vector_remove(vector* vec, size_t i){
	int x;
	if(i >= vec->length)
		return;
	free(vec->data[i]);
	vec->length--;
	for(x=i;x<vec->length;++x)
		vec->data[x] = vec->data[x+1];
}

int vector_index(vector* vec, void* data, size_t n){
	int x;
	void* check;
	for(x=0;x<vec->length;++x){
		check = vector_get(vec, x);
		if(check==data||memcmp(check, data, n)==0){
			return x;
		}
	}
	return -1;
}

void destroy_vector(vector* vec){
	int i;
	for(i=0;i<vec->length;i++){
	free(vec->data[i]);
	}
	free(vec->data);
	free(vec);
}


