#include "map.h"
#include "vector.h"
#include <stdio.h>
#include <unistd.h>

int main(void){
	map* m = create_map();
	int h;
	char* res;
	map_put(m, "key", (void*)"val", 4);
	map_put(m, "key", (void*)"val2", 5);
	printf("map size: %d\n", m->size);
	res = (char*)map_get(m, "key");
	printf("key: %s\n", res);
	map_remove(m, "key");
	printf("map size: %d\n", m->size);
	destroy_map(m);
	return 0;
}
