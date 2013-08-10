#include "list.h"
#include <stdlib.h>
#include <string.h>


list_p create_list(){
	list_p list = (list_p) malloc(sizeof(struct list));
	list->length = 0;
	list->first = NULL;
	list->last = NULL;
	list->destructor = free;
	return list;
}

list_iter_p list_iterator(list_p list, char init){
	list_iter_p iter = (list_iter_p)malloc(sizeof(struct list_iter));
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

void list_add(list_p list, void* data, int size){
	lnode_p node = (lnode_p)malloc(sizeof(struct linked_node));
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

void* list_current(list_iter_p iter){
	if(iter->started&&iter->current!=NULL)
		return iter->current->data;
	return NULL;
}

void* list_next(list_iter_p iter){
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

void* list_prev(list_iter_p iter){
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

void* list_first(list_p list){
	return list->first->data;
}

void* list_last(list_p list){
	return list->last->data;
}

void* list_pop(list_p list){
	lnode_p last = list->last;
	if(last == NULL) return NULL;

	if (list->first == list->last) {
		list->first = NULL;
		list->last = NULL;
	} else {
		list->last = last->prev;
		last->prev->next = NULL;
	}
		
	void* data = last->data;
	free(last);
	list->length--;
	return data;
}

void* list_poll(list_p list){
	lnode_p first = list->first;
	
	if(first == NULL)
		return NULL;
	
	if (list->first == list->last) {
		list->first = NULL;
		list->last = NULL;
	} else {
		list->first = first->next;
		first->next->prev = NULL;
	}

	void* data = first->data;
	free(first);
	list->length--;
	return data;
}

void list_remove(list_p list, char end){
	void * data;
	if(end == FRONT)
		data = list_poll(list);
	else if (end == BACK)
		data = list_pop(list);
	else return;
	list->destructor(data);
}

void destroy_list(list_p list){
	lnode_p cur = list->first;
	lnode_p next;
	while(cur!=NULL){
		next = cur->next;
		list->destructor(cur->data);
		free(cur);
		cur = next;
	}
	free(list);
}

void list_insert(list_p list, lnode_p before, void *data, int size){
    if (list->first == NULL) {
        list_add(list, data, size);
    } 
    else if (before == list->last) {
        list_add(list, data, size);
    }
    else if (before == NULL) {
        lnode_p node = (lnode_p)malloc(sizeof(struct linked_node));
        node->data = malloc(size);
        memcpy(node->data, data, size);

        node->next = list->first;
        node->prev = NULL;
        node->next->prev = node;
        list->first = node;
        list->length++;
    }
    else {
        lnode_p node = (lnode_p)malloc(sizeof(struct linked_node));
        node->data = malloc(size);
        memcpy(node->data, data, size);

        node->next = before->next;
        node->prev = before;
        before->next = node;
        node->next->prev = node;
        list->length++;
    }
}

void* list_pluck(list_p list, lnode_p removed){
    if(removed == NULL){
        return NULL;
    }
    else if(list->first == removed && list->last == removed){
        list->first = NULL;
        list->last = NULL;
    }
    else if(list->first == removed){
        list->first = removed->next;
        removed->next->prev = NULL;
    }
    else if(list->last == removed){
        list->last = removed->prev;
        removed->prev->next = NULL;
    }
    else{
        removed->prev->next = removed->next;
        removed->next->prev = removed->prev;
    }

    void* data = removed->data;
    free(removed);
    list->length--;
    return data;
}