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
	void (*destructor)(void*);
} hashmap;

/* Create a new hashmap. The hashmap created by this method must be eventually 
   destroyed by a call to destroy_hashmap() to avoid memory leak */
hashmap* create_hashmap();

/* Place an entry with the value val and length len into the hashmap m and associate
   it with the key key. The key and value are copied by value, not by pointer,
   so if they were created on the heap, they must be freed later. */
void hashmap_put(hashmap* m, char* key, void* val, size_t len);

/* Get the value of the entry in hashmap m associated with key key */
void* hashmap_get(hashmap* m, char* key);

/* Remove the item associated with the key key in the hashmap m. The memory for the
   entry is completely freed, so use hashmap_get and make a deep copy if you wish to
   retain it. */
void hashmap_remove(hashmap* m, char* key);

/* Hash function for the key key. This function is not meant to be called directly */
size_t hash_func(char * key);

/* Free all of the memory associated with hashmap m */
void destroy_hashmap(hashmap* m);

#endif
