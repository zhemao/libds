#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int intcmpfunc(void* a, void* b){
	int *ia, *ib;
	ia = (int*) a;
	ib = (int*) b;
	return *ia - *ib;
}

void print_data(void * data){
	int * pi = (int*) data;
	printf("%d\n", *pi);
}

void insert_int(tree_p tr, int x){
	rb_insert(tr, &x, sizeof(int));
}

void print_successor(tnode_p node){
	int *pia, *pib;
	tnode_p next = tree_successor(node);
	pia = (int*) node->data;
	pib = (int*) next->data;
	printf("The successor to %d is %d\n", *pia, *pib);
}

void findthree(tree_p tr){
	int x = 3;
	tnode_p node = tree_search(tr, &x);
	if(node != NULL)
		printf("We found it!\n");
}

int main(void){
	struct tree tr;
	tr.root = NULL;
	tr.cmpfunc = intcmpfunc;

	insert_int(&tr, 15);
	insert_int(&tr, 5);
	insert_int(&tr, 3);
	insert_int(&tr, 12);
	insert_int(&tr, 10);
	insert_int(&tr, 6);
	insert_int(&tr, 7);
	insert_int(&tr, 16);
	insert_int(&tr, 20);
	insert_int(&tr, 18);
	insert_int(&tr, 23);

	findthree(&tr);

	traverse(tr.root, print_data);

	print_successor(tr.root->left);

	rb_delete(&tr, tr.root->left);
	rb_delete(&tr, tr.root->left->right);
	rb_delete(&tr, tr.root->left->left);
	/*left_rotate(&tr, tr.root->right);
	right_rotate(&tr, tr.root->right);*/

	traverse(tr.root, print_data);

	destroy_node(tr.root);

	return 0;
}
