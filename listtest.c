#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv){
	printf("%ld\n", sizeof(linked_list));
	printf("%ld\n", sizeof(struct linked_node));
	linked_list* list = create_list();
	linked_list* list2 = create_list();
	int x;
	int * pi;
	
	for(x=0;x<10;x++){
		list_add(list, (void*)&x, sizeof(int));
		list_add(list2, (void*)&x, sizeof(int));
	}
	
	list_iter* iter = list_iterator(list, FRONT);
	
	while(list_next(iter)!=NULL){
		pi = (int*)list_current(iter);
		printf("%d\n", *pi);
	}

	destroy_list(list);
	
	list_remove(list2, FRONT);
	list_remove(list2, BACK);

	free(iter);
	iter = list_iterator(list2, 1);
	
	while(list_prev(iter)!=NULL){
		pi = (int*)list_current(iter);
		printf("%d\n", *pi);
	}
	destroy_list(list2);
	free(iter);
}
