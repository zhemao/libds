#ifndef LIST_H
#define LIST_H

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
} linked_list;

typedef struct{
	nodeptr current;
	char started;
} list_iter;

linked_list* create_list();
list_iter* list_iterator(linked_list* list, char init);
void list_add(linked_list* list, void* data, int size);
void* list_current(list_iter* list);
void* list_next(list_iter* list);
void* list_prev(list_iter* list);
void* list_first(linked_list* list);
void* list_last(linked_list* list);
void* list_pop(linked_list* list);
void* list_poll(linked_list* list);
void list_remove(linked_list* list, char end);
void* destroy_list(linked_list* list);

#endif
