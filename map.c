#include "map.h"
#include <string.h>

map* create_map(){
	map* m = (map*)malloc(sizeof(map));
	int i;
	m->size=0;
	m->buckets = (item**)malloc(sizeof(item*)*NUM_BUCKETS);
	for(i=0;i<NUM_BUCKETS;++i)
		m->buckets[i] = NULL;
	m->keys = create_vector();
	m->destructor = free;
	return m;
}

void* map_get(map* m, char * key){
	if(key==NULL){
		return NULL;
	}
	size_t h = hash_func(key);
	item* itm = m->buckets[h];
	while(itm!=NULL){
		if(strcmp(key, itm->key)==0)
			return itm->val;
		itm = itm->next;
	}
	return NULL;
}

void map_put(map* m, char* key, void* val, size_t len){
	int keylen = strlen(key);
	size_t h = hash_func(key);
	item* itm = m->buckets[h];
	item* last = NULL;
	while(itm!=NULL){
		if(strcmp(key, itm->key)==0){
		if(itm->val!=NULL) m->destructor(itm->val);
		itm->val = malloc(len);
		memcpy(itm->val, val, len);
			return;
		}
		if(itm->next==NULL) last = itm;
		itm = itm->next;
	}
	itm = (item*)malloc(sizeof(item));
	itm->key = malloc(keylen+1);
	memcpy(itm->key, key, keylen+1);
	itm->val = malloc(len);
	memcpy(itm->val, val, len);
	itm->next = NULL;
	if(last==NULL) m->buckets[h] = itm;
	else last->next = itm;
	vector_add(m->keys, itm->key, keylen);
	m->size++;
}

void map_remove(map* m, char* key){
	int n = strlen(key);
	size_t h = hash_func(key);
	item *itm = m->buckets[h];
	item *last = NULL;
	int keyind;
	while(itm!=NULL){
		if(strcmp(key, itm->key)==0){
		if(last==NULL)
		m->buckets[h] = NULL;
		if(last!=NULL)
		last->next = itm->next;
		free(itm->key);
		m->destructor(itm->val);
		free(itm);
		keyind = vector_index(m->keys, key, n);
		vector_remove(m->keys, keyind);
		m->size--;
		return;
	}
	last = itm;
		itm = itm->next;
	}
}

/* Uses FNV hash function, as given by Julien Walker's "The Art of Hashing" */
size_t hash_func(char * key){
	size_t h = 2166136261;
	int i;
	for (i=0; key[i]!='\0'; ++i)
		h = ( h * 16777619 ) ^ key[i];
	return h % NUM_BUCKETS;
}

void destroy_map(map* m){
	int x;
	item* itm;
	for(x=0;x<NUM_BUCKETS;++x){
	itm = m->buckets[x];
		while(itm!=NULL){
			free(itm->key);
			m->destructor(itm->val);
			free(itm);
			itm = itm->next;
		}
	}
	destroy_vector(m->keys);
	free(m->buckets);
	free(m);
}
