#ifndef __LIBDS_LIST_H__
#define __LIBDS_LIST_H__

/* A C implementation of a doubly-linked list. Contains void pointer values.
   Can be used as a LIFO stack of FIFO queue. */

#define FRONT 0
#define BACK 1

struct linked_node{
	void* data;
	struct linked_node* next;
	struct linked_node* prev;
};

typedef struct linked_node* lnode_p;

struct list{
	int length;
	lnode_p first;
	lnode_p last;
	void (*destructor)(void*);
};

typedef struct list * list_p;

struct list_iter{
	lnode_p current;
	char started;
};

typedef struct list_iter * list_iter_p;

/* Create a linked_list object. This pointer is created on the heap and must be
   cleared with a call to destroy_list to avoid memory leaks */
list_p create_list();

/* Create a list_iter object for the linked_list list. The flag init can be 
   either FRONT or BACK and indicates whether to start the iterator from the first
   or last item in the list */
list_iter_p list_iterator(list_p list, char init);

/* Add an item with the given value and size to the back of the list. 
   The data is copied by value, so the original pointer must be freed if it
   was allocated on the heap. */
void list_add(list_p list, void* data, int size);

/* Gets the data stored in the first item of the list or NULL if the list is empty */
void* list_first(list_p list);
/* Gets the data stored in the last item of the list or NULL if the list is empty */
void* list_last(list_p list);

/* Removes the last item in the list (LIFO order) and returns the data stored 
   there. The data returned must be freed later in order to remain memory safe. */
void* list_pop(list_p list);
/* Removes the first item in the list (FIFO order) and returns the data stored 
   there. The data return must be freed later in order to remain memory safe. */
void* list_poll(list_p list);
/* Convenience function for completely destroying an item in the list. If the end
   flag is FRONT, an item will be polled from the front of the list and its data
   freed. If the end flag is set to BACK, an item will be popped off the end of 
   the list and the data freed. */
void list_remove(list_p list, char end);

/* Completely free the data associated with the list. */
void destroy_list(list_p list);

/* Return the data held by the current item pointed to by the iterator */
void* list_current(list_iter_p list);
/* Advances the iterator to the next item in the list and returns the data 
   stored there. */
void* list_next(list_iter_p list);
/* Advances the iterator to the previous item in the list and returns the data 
   stored there. */
void* list_prev(list_iter_p list);

#endif
#ifndef __LIBDS_VECTOR_H__
#define __LIBDS_VECTOR_H__

/* A C implementation of a vector, or dynamically expanding array. */

#include <stdlib.h>

#define BASE_CAP 10
#define EXPAND_RATIO 1.5

struct vector{
	void** data;
	int * sizes;
	size_t length;
	size_t capacity;
	void (*destructor)(void*);
};

typedef struct vector * vector_p;

/* Create a vector object. It must be eventually destroyed by a call to 
   destroy_vector to avoid memory leaks. */
vector_p create_vector();
/* Create a new vector that is composed of the items in the old vector with
   indices in the range of [start,end) */
vector_p subvector(vector_p vec, int start, int end);
/* Add an item to the end of the vector */
void vector_add(vector_p vec, void* data, size_t n);
/* Get the item at index i of the vector */
void* vector_get(vector_p vec, size_t i);
/* Set the item at index i of the vector to the data provided. */
int vector_set(vector_p vec, size_t i, void* data, size_t n);
/* Insert the data at index i of the vector and shift the other 
   items to the right. */
int vector_insert(vector_p vec, size_t i, void* data, size_t n);
/* Get the index of the item in the vector that is equal to the data. 
   Equality is defined as having the same bytes in memory. */
int vector_index(vector_p vec, void* data, size_t n);
/* Remove the item at index i of the vector and free its memory */
void vector_remove(vector_p vec, size_t i);
/* Check to make sure there is still room in the vector and expand it if 
   necessary. This function is not meant to be called directly. */
void check_length(vector_p vec);
/* Destroy the vector and free all the memory associated with it. */
void destroy_vector(vector_p vec);
/* Swaps the pointers at indices i and j in the vector */
void vector_swap(vector_p vec, int i, int j);


#endif
#ifndef __LIBDS_HASHMAP_H__
#define __LIBDS_HASHMAP_H__

/* A C implementation of a Hash Map. 
   Uses string keys but has void pointer values */

#include <stdlib.h>

#include <time.h>

#define NUM_BUCKETS 3848921

struct item{
	char* key;
	void* val;
	time_t expiry;
	struct item * next;
};

typedef struct item item_t;

struct hashmap{
	item_t** buckets;
	size_t size;
	vector_p keys;
	void (*destructor)(void*);
};

typedef struct hashmap * hashmap_p;

/* Create a new hashmap. The hashmap created by this method must be eventually 
   destroyed by a call to destroy_hashmap() to avoid memory leak */
hashmap_p create_hashmap();

/* Place an entry with the value val and length len into the hashmap m and associate
   it with the key key. The key and value are copied by value, not by pointer,
   so if they were created on the heap, they must be freed later. */
void hashmap_put(hashmap_p m, char* key, void* val, size_t len);

/* Get the value of the entry in hashmap m associated with key key */
void* hashmap_get(hashmap_p m, char* key);

/* Remove the item associated with the key key in the hashmap m. The memory for the
   entry is completely freed, so use hashmap_get and make a deep copy if you wish to
   retain it. */
void hashmap_remove(hashmap_p m, char* key);

/* Hash function for the key key. This function is not meant to be called directly */
size_t hash_func(char * key);

/* Free all of the memory associated with hashmap m */
void destroy_hashmap(hashmap_p m);

#endif
#ifndef __LIBDS_STRUTILS_H__
#define __LIBDS_STRUTILS_H__

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
/* concatenate n characters of string str in the buffer, expanding the buffer
   if necessary */
void buffer_nconcat(stringbuf * buf, char * str, int n);
/* writes the characters in str into the buffer, 
   expanding the buffer if necessary */
void buffer_write(stringbuf * buf, char * str);
/* writes n characters from str into the buffer, expanding the buffer if 
   necessary */
void buffer_nwrite(stringbuf * buf, char * str, int n);
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
char ** str_split(char * str, char * delim, int * size);
/* free the elements of a string array, as well as the array itself */
void free_str_array(char ** arr, int len);
/* strip trailing whitespace and newline characters from a string */
void str_strip(char * str, int len);
/* convert the characters in a string to lowercase */
void str_lower(char * str);
/* convert the characters in the string to uppercase */
void str_upper(char * str);
/* tests whether stra is starts with the string strb */
int str_startswith(char * stra, char * strb);
/* tests whether stra ends with the string strb */
int str_endswith(char * stra, char * strb);
#endif /* __STRUTILS_H__ */


#ifndef __LIBDS_HEAP_H__
#define __LIBDS_HEAP_H__



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
typedef int (*heapcmpfunc)(vector_p, int, int);

struct heap {
	vector_p vec;
	heapcmpfunc cmpfunc;
};

typedef struct heap * heap_p;

heap_p create_heap(heapcmpfunc cmpfunc);
void destroy_heap(heap_p hp);

/* maintain the heap property starting at index i */
void heapify(heap_p hp, int i);
/* build the heap */
void build_heap(heap_p hp);
/* removes the first element from the heap and then adjusts to maintain the 
   heap property */
void heap_remove(heap_p hp);
/* inserts the value into the heap such that the heap property is maintained */
void heap_insert(heap_p hp, void * val, int size);

#endif /* __HEAP_H__ */

#ifndef __LIBDS_TREE_H__
#define __LIBDS_TREE_H__

#include <stdlib.h>

enum {
	RED,
	BLACK
};

typedef int (*treecmpfunc)(void*,void*);

struct tree_node {
	struct tree_node * left;
	struct tree_node * right;
	struct tree_node * parent;
	void * data;
	int color;
};

typedef struct tree_node * tnode_p;

tnode_p make_node(void*, int);

struct tree {
	tnode_p root;
	treecmpfunc cmpfunc;
};

typedef struct tree * tree_p;
typedef void (*traversecb)(void*);

tnode_p tree_insert(tree_p tr, void * data, int size);
void tree_delete(tree_p tr, tnode_p node);

void left_rotate(tree_p tr, tnode_p node);
void right_rotate(tree_p tr, tnode_p node);

tnode_p tree_minimum(tnode_p node);
tnode_p tree_maximum(tnode_p node);

tnode_p tree_predecessor(tnode_p node);
tnode_p tree_successor(tnode_p node);

tnode_p tree_search(tree_p tr, void * key);
void traverse(tnode_p node, traversecb);

void destroy_node(tnode_p node);

int rb_color(tnode_p node);
tnode_p rb_insert(tree_p tr, void * data, int size);
void rb_delete(tree_p tr, tnode_p node);

#endif
