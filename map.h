#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include "vector.h"
#include <time.h>

#define NUM_BUCKETS 3848921

struct item_t{
	char* key;
	void* val;
	time_t expiry;
	struct item_t * next;
};

typedef struct item_t item;

typedef struct{
	item** buckets;
	size_t size;
	vector* keys;
} map;

map* create_map();
void map_put(map* m, char* key, void* val, size_t len);
void* map_get(map* m, char* key);
void map_remove(map* m, char* key);
size_t hash_func(char * key);
void destroy_map(map* m);

#endif
