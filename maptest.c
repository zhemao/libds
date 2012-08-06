#include "hashmap.h"
#include "vector.h"
#include <stdio.h>
#include <unistd.h>

int main(void){
	hashmap_p m = create_hashmap();
	char* res;
	hashmap_put(m, "key", (void*)"val", 4);
	hashmap_put(m, "key", (void*)"val2", 5);
	printf("hashmap size: %d\n", (int) m->size);
	res = (char*)hashmap_get(m, "key");
	printf("key: %s\n", res);
	hashmap_remove(m, "key");
	printf("hashmap size: %d\n", (int) m->size);

	hashmap_put(m, "key1", (void*)"val1", 5);
	hashmap_put(m, "key2", (void*)"val2", 5);
	hashmap_put(m, "key3", (void*)"val3", 5);

	hashmap_resize(m, 211);

	res = (char*) hashmap_get(m, "key1");
	printf("key: %s\n", res);
	printf("num_buckets: %d\n", (int) m->num_buckets);

	destroy_hashmap(m);
	return 0;
}
