#ifndef LIST_H
#define LIST_H

/* A C implementation of a doubly-linked list. Contains void pointer values.
   Can be used as a LIFO stack of FIFO queue. */

#define FRONT 0
#define BACK 1

struct linked_node{
	void* data;
	struct linked_node* next;
	struct linked_node* prev;
} linked_node;

typedef struct linked_node* nodeptr;

typedef struct{
	int length;
	nodeptr first;
	nodeptr last;
	void (*destructor)(void*);
} linked_list;

typedef struct{
	nodeptr current;
	char started;
} list_iter;

/* Create a linked_list object. This pointer is created on the heap and must be
   cleared with a call to destroy_list to avoid memory leaks */
linked_list* create_list();

/* Create a list_iter object for the linked_list list. The flag init can be 
   either FRONT or BACK and indicates whether to start the iterator from the first
   or last item in the list */
list_iter* list_iterator(linked_list* list, char init);

/* Add an item with the given value and size to the back of the list. 
   The data is copied by value, so the original pointer must be freed if it
   was allocated on the heap. */
void list_add(linked_list* list, void* data, int size);

/* Gets the data stored in the first item of the list or NULL if the list is empty */
void* list_first(linked_list* list);
/* Gets the data stored in the last item of the list or NULL if the list is empty */
void* list_last(linked_list* list);

/* Removes the last item in the list (LIFO order) and returns the data stored 
   there. The data returned must be freed later in order to remain memory safe. */
void* list_pop(linked_list* list);
/* Removes the first item in the list (FIFO order) and returns the data stored 
   there. The data return must be freed later in order to remain memory safe. */
void* list_poll(linked_list* list);
/* Convenience function for completely destroying an item in the list. If the end
   flag is FRONT, an item will be polled from the front of the list and its data
   freed. If the end flag is set to BACK, an item will be popped off the end of 
   the list and the data freed. */
void list_remove(linked_list* list, char end);

/* Completely free the data associated with the list. */
void* destroy_list(linked_list* list);

/* Return the data held by the current item pointed to by the iterator */
void* list_current(list_iter* list);
/* Advances the iterator to the next item in the list and returns the data 
   stored there. */
void* list_next(list_iter* list);
/* Advances the iterator to the previous item in the list and returns the data 
   stored there. */
void* list_prev(list_iter* list);

#endif
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
	void (*destructor)(void*);
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
#ifndef MAP_H
#define MAP_H

/* A C implementation of a Hash Map. 
   Uses string keys but has void pointer values */

#include <stdlib.h>

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
#ifndef __STRUTILS_H__
#define __STRUTILS_H__

#include <stdio.h>


typedef struct {
	char * str;
	int length;
	int capacity;
} stringbuf;

/* makes a string buffer with the given initial capacity */
stringbuf * make_buffer(int capacity);
/* concatenate the string str into the string buffer, expanding the buffer
   if necessary */
void buffer_concat(stringbuf * buf, char * str);
/* writes the characters in str, followed by a NULL character, into the buffer,
   expanding the buffer if necessary */
void buffer_write(stringbuf * buf, char * str);
/* reallocate the buffer's internal string if the length of the string exceeds
   its capacity */
void realloc_if_needed(stringbuf * buf);
/* free the buffer and its internal string */
void destroy_buffer(stringbuf * buf);
/* safely read the entire contents of the file into a properly sized string */
char * saferead(FILE * f);
/* join an array of strings of length len with separator sep */
char* str_join(char **args, char * sep, int len);
/* split the string into a vector around the delimiter string */
vector* str_split(char * str, char * delim);
/* strip trailing whitespace and newline characters from a string */
void str_strip(char * str, int len);
/* convert the characters in a string to lowercase */
void str_lower(char * str);
/* convert the characters in the string to uppercase */
void str_upper(char * str);

#endif /* __STRUTILS_H__ */


