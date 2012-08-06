#include "vector.h"
#include <string.h>

vector_p create_vector(){
	vector_p vec = (vector_p)malloc(sizeof(struct vector));
	vec->data = (void**)malloc(sizeof(void*)*BASE_CAP);
	vec->sizes = (int*)malloc(sizeof(int)*BASE_CAP);
	vec->capacity = BASE_CAP;
	vec->length = 0;
	vec->destructor = free;
	return vec;
}

vector_p subvector(vector_p vec, int start, int end){
	vector_p subvec = create_vector();
	int i;
	void * val;
	for(i=start; i<end; i++){
		val = vec->data[i];
		vector_add(subvec, val, vec->sizes[i]);
	}
	return subvec;
}

void check_length(vector_p vec){
	if(vec->length >= vec->capacity){
		vec->capacity*=EXPAND_RATIO;
		vec->data = (void**)realloc((void*)vec->data, 
									vec->capacity*sizeof(void*));
		vec->sizes = (int*)realloc((void*)vec->sizes, 
									vec->capacity*sizeof(int));
	}
}

void vector_add(vector_p vec, void* data, size_t n){
	check_length(vec);
	vec->data[vec->length] = malloc(n);
	vec->sizes[vec->length] = n;
	memcpy(vec->data[vec->length], data, n);
	vec->length++;
}

void* vector_get(vector_p vec, size_t i){
	if(i >= vec->length)
		return NULL;
	return vec->data[i];
}

int vector_set(vector_p vec, size_t i, void* data, size_t n){
	if(i >= vec->length)
		return -1;
	vec->destructor(vec->data[i]);
	vec->data[i] = malloc(n);
	vec->sizes[i] = n;
	memcpy(vec->data[i], data, n);
	return 0;
}

int vector_insert(vector_p vec, size_t i, void* data, size_t n){
	int x;
	
	if(i > vec->length)
		return -1;
	
	check_length(vec);
	for(x=vec->length;x>=i;x--){
		vec->data[x+1] = vec->data[x];
		vec->sizes[x+1] = vec->sizes[x+1];
	}
	vec->data[i] = malloc(n);
	vec->sizes[i] = n;
	memcpy(vec->data[i], data, n);
	vec->length++;
	return 0;
}

void vector_remove(vector_p vec, size_t i){
	int x;
	if(i >= vec->length)
		return;
	vec->destructor(vec->data[i]);
	vec->length--;
	for(x=i;x<vec->length;++x){
		vec->data[x] = vec->data[x+1];
		vec->sizes[x] = vec->sizes[x+1];
	}
}

int vector_index(vector_p vec, void* data, size_t n){
	int x;
	void* check;
	for(x=0;x<vec->length;++x){
		check = vec->data[x];
		if(check==data||memcmp(check, data, n)==0){
			return x;
		}
	}
	return -1;
}

void destroy_vector(vector_p vec){
	int i;
	for(i=0;i<vec->length;i++){
		vec->destructor(vec->data[i]);
	}
	free(vec->data);
	free(vec->sizes);
	free(vec);
}


void vector_swap(vector_p vec, int i, int j){
	void * temp;
	
	if(i >= vec->length || j >= vec->length)
		return;
		
	temp = vec->data[i];
	vec->data[i] = vec->data[j];
	vec->data[j] = temp;	
}

