#ifndef MAP_H
#define MAP_H

/* A C implementation of a Hash Map. 
   Uses string keys but has void pointer values */

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

/* Create a new map. The map created by this method must be eventually 
   destroyed by a call to destroy_map() to avoid memory leak */
map* create_map();

/* Place an entry with the value val and length len into the map m and associate
   it with the key key. The key and value are copied by value, not by pointer,
   so if they were created on the heap, they must be freed later. */
void map_put(map* m, char* key, void* val, size_t len);

/* Get the value of the entry in map m associated with key key */
void* map_get(map* m, char* key);

/* Remove the item associated with the key key in the map m. The memory for the
   entry is completely freed, so use map_get and make a deep copy if you wish to
   retain it. */
void map_remove(map* m, char* key);

/* Hash function for the key key. This function is not meant to be called directly */
size_t hash_func(char * key);

/* Free all of the memory associated with map m */
void destroy_map(map* m);

#endif
