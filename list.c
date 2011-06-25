#include "list.h"
#include <stdlib.h>
#include <string.h>


linked_list* create_list(){
	linked_list* list = (linked_list*) malloc(sizeof(linked_list));
	list->length = 0;
	list->first = NULL;
	list->last = NULL;
	return list;
}

list_iter* list_iterator(linked_list* list, char init){
	list_iter* iter = (list_iter*)malloc(sizeof(list_iter));
	if(init==FRONT){
		iter->current = list->first;
	}
	else if(init==BACK){
		iter->current = list->last;
	}
	else return NULL;
	iter->started = 0;
	return iter;
}

void list_add(linked_list* list, void* data, int size){
	nodeptr node = (nodeptr)malloc(sizeof(struct linked_node));
	node->data = malloc(size);
	memcpy(node->data, data, size);
	
	if(list->first==NULL){
		node->prev = NULL;
		node->next = NULL;
		list->first = node;
		list->last = node;
	}
	else{
		list->last->next = node;
		node->prev = list->last;
		node->next = NULL;
		list->last = node;
	}
	list->length++;
}

void* list_current(list_iter* iter){
	if(iter->started&&iter->current!=NULL)
		return iter->current->data;
	return NULL;
}

void* list_next(list_iter* iter){
	if(!iter->started&&iter->current!=NULL){
		iter->started=1;
		return iter->current->data;
	}
	if(iter->current!=NULL){
		iter->current = iter->current->next;
		return list_current(iter);
	}
	return NULL;
}

void* list_prev(list_iter* iter){
	if(!iter->started&&iter->current!=NULL){
		iter->started=1;
		return iter->current->data;
	}
	if(iter->current!=NULL){
		iter->current = iter->current->prev;
		return list_current(iter);
	}
	return NULL;
}

void* list_first(linked_list* list){
	return list->first->data;
}

void* list_last(linked_list* list){
	return list->last->data;
}

void* list_pop(linked_list* list){
	nodeptr last = list->last;
	if(last == NULL) return NULL;
	list->last = last->prev;
	void* data = last->data;
	last->prev->next = NULL;
	free(last);
	return data;
}

void* list_poll(linked_list* list){
	nodeptr first = list->first;
	if(first == NULL) return NULL;
	list->first = first->next;
	void* data = first->data;
	first->next->prev = NULL;
	free(first);
	return data;
}

void list_remove(linked_list* list, char end){
	void * data;
	if(end == FRONT)
		data = list_poll(list);
	else if (end == BACK)
		data = list_pop(list);
	else return;
	free(data);
}

void* destroy_list(linked_list* list){
	nodeptr cur = list->first;
	nodeptr next;
	while(cur!=NULL){
		next = cur->next;
		free(cur->data);
		free(cur);
		cur = next;
	}
	free(list);
}

