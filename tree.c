#include "tree.h"
#include <string.h>

tnode_p make_node(void * data, int size){
	tnode_p node = (tnode_p)malloc(sizeof(struct tree_node));
	node->data = malloc(size);
	memcpy(node->data, data, size);
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void tree_insert(tree_p tr, void * data, int size){
	tnode_p node = make_node(data, size);
	tnode_p parent = NULL;
	tnode_p current = tr->root;

	while(current != NULL){
		parent = current;
		if(tr->cmpfunc(node->data, current->data) < 0){
			current = current->left;
		} else {
			current = current->right;
		}
	}

	node->parent = parent;
	if(parent == NULL)
		tr->root = node;
	else if(tr->cmpfunc(node->data, parent->data) < 0)
		parent->left = node;
	else parent->right = node;
}

void tree_delete(tree_p tr, tnode_p node){
	tnode_p parent, current, next;

	if(node->left == NULL || node->right == NULL)
		current = node;
	else current = tree_successor(node);

	parent = current->parent;

	if(current->left != NULL)
		next = current->left;
	else next = current->right;

	if(next != NULL)
		next->parent = parent;

	if(parent == NULL)
		tr->root = next;
	else if(current == parent->left)
		parent->left = next;
	else parent->right = next;

	free(node->data);

	if(node != current)
		node->data = current->data;
	
	current->parent = current->left = current->right = NULL;
	free(current);

}

tnode_p tree_predecessor(tnode_p node){
	tnode_p next;

	if(node->left == NULL){
		next = node->parent;
		
		while(next != NULL && node == next->left){
			node = next;
			next = next->parent;
		}
		return next;
	}

	next = node->left;

	while(next->right != NULL)
		next = next->right;

	return next;
}

tnode_p tree_successor(tnode_p node){
	tnode_p next;
	
	if(node->right == NULL){
		next = node->parent;
		
		while(next != NULL && node == next->right){
			node = next;
			next = next->parent;
		}
		return next;
	}

	next = node->right;

	while(next->left != NULL)
		next = next->left;

	return next;
}

void traverse(tnode_p node, traversecb tcb){
	if(node != NULL){
		tcb(node->data);
		traverse(node->left, tcb);
		traverse(node->right, tcb);
	}
}

void left_rotate(tree_p tr, tnode_p node){
	tnode_p right = node->right;
	if(right == NULL) return;
	
	node->right = right->left;
	if(right->left != NULL)
		right->left->parent = node;

	right->parent = node->parent;

	if(node->parent == NULL)
		tr->root = right;
	else if(node->parent->left == node)
		node->parent->left = right;
	else node->parent->right = right;

	right->left = node;
	node->parent = right;
}

void right_rotate(tree_p tr, tnode_p node){
	tnode_p left = node->left;
	if(left == NULL) return;

	node->left = left->right;
	if(left->right != NULL)
		left->right->parent = node;

	left->parent = node->parent;

	if(node->parent == NULL)
		tr->root = left;
	else if(node->parent->left == node)
		node->parent->left = left;
	else node->parent->right = left;

	left->right = node;
	node->parent = left;
}

void destroy_node(tnode_p node){
	if(node->left != NULL) destroy_node(node->left);
	if(node->right != NULL) destroy_node(node->right);

	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	free(node->data);
	node->data = NULL;
	free(node);
}
