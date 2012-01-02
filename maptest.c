#include "hashmap.h"
#include "vector.h"
#include <stdio.h>
#include <unistd.h>

int main(void){
	hashmap_p m = create_hashmap();
	char* res;
	hashmap_put(m, "key", (void*)"val", 4);
	hashmap_put(m, "key", (void*)"val2", 5);
	printf("hashmap size: %d\n", m->size);
	res = (char*)hashmap_get(m, "key");
	printf("key: %s\n", res);
	hashmap_remove(m, "key");
	printf("hashmap size: %d\n", m->size);
	destroy_hashmap(m);
	return 0;
}
