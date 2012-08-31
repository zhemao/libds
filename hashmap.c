#include "hashmap.h"
#include <string.h>

hashmap_p create_hashmap(){
	hashmap_p m = (hashmap_p)malloc(sizeof(struct hashmap));
	int i;
	m->size=0;
	m->num_buckets = DEFAULT_NUM_BUCKETS;
	m->buckets = (item_t**) malloc(sizeof(item_t*) * m->num_buckets);
	for(i=0; i < m->num_buckets; i++)
		m->buckets[i] = NULL;
	m->keys = create_vector();
	m->destructor = free;
	return m;
}

void* hashmap_get(hashmap_p m, char * key){
	if(key==NULL){
		return NULL;
	}
	size_t h = hash_func(key) % m->num_buckets;
	item_t* itm = m->buckets[h];
	while(itm!=NULL){
		if(strcmp(key, itm->key)==0)
			return itm->val;
		itm = itm->next;
	}
	return NULL;
}

void hashmap_put(hashmap_p m, char* key, void* val, size_t len){
	int keylen = strlen(key);
	size_t h = hash_func(key) % m->num_buckets;
	item_t* itm = m->buckets[h];
	item_t* last = NULL;
	
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
	
	itm = (item_t*)malloc(sizeof(item_t));
	itm->key = malloc(keylen+1);
	memcpy(itm->key, key, keylen+1);
	itm->val = malloc(len);
	memcpy(itm->val, val, len);
	itm->next = NULL;
	if(last==NULL) m->buckets[h] = itm;
	else last->next = itm;
	vector_add(m->keys, itm->key, keylen+1);
	m->size++;
}

void hashmap_remove(hashmap_p m, char* key){
	int n = strlen(key);
	size_t h = hash_func(key) % m->num_buckets;
	item_t *itm = m->buckets[h];
	item_t *last = NULL;
	int keyind;
	while(itm!=NULL){
		if(strcmp(key, itm->key)==0)
			break;
		last = itm;
		itm = itm->next;
	}
	
	if(itm != NULL){
		if(last==NULL)
			m->buckets[h] = itm->next;
		else last->next = itm->next;
		
		free(itm->key);
		m->destructor(itm->val);
		free(itm);
		
		keyind = vector_index(m->keys, key, n);
		vector_remove(m->keys, keyind);
		m->size--;
	}
}

/* Uses FNV hash function, as given by Julien Walker's "The Art of Hashing" */
size_t hash_func(char * key){
	size_t h = 2166136261;
	int i;
	for (i=0; key[i]!='\0'; ++i)
		h = ( h * 16777619 ) ^ key[i];
	return h;
}

void destroy_hashmap(hashmap_p m){
	int x;
	item_t* itm;
	for(x=0;x<m->num_buckets;++x){
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

void hashmap_resize(hashmap_p m, size_t num_buckets){
	int i;
	
	m->buckets = (item_t **)realloc(m->buckets, 
					sizeof(item_t *) * num_buckets);

	for(i=0; i < m->size; i++){
		char* key = (char*) vector_get(m->keys, i);
		int h = hash_func(key) % m->num_buckets;
		item_t *prev = NULL;
		item_t *cur = m->buckets[h];

		while(cur != NULL){
			if(strcmp(cur->key, key)==0)
				break;
			prev = cur;
			cur = cur->next;
		}

		if(cur != NULL){
			if(prev == NULL)
				m->buckets[h] = cur->next;
			else prev->next = cur->next;
			cur->next = NULL;
		}

		h = hash_func(key) % num_buckets;

		prev = m->buckets[h];

		if(prev == NULL)
			m->buckets[h] = cur;
		else {
			while(prev->next != NULL)
				prev = prev->next;
			prev->next = cur;
		}
	}

	m->num_buckets = num_buckets;
}
