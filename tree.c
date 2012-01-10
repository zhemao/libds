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

tnode_p tree_insert(tree_p tr, void * data, int size){
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

	return node;
}

static tnode_p pull_out(tree_p tr, tnode_p node){
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

	current->data = NULL;

	return current;
}

void tree_delete(tree_p tr, tnode_p node){
	tnode_p current = pull_out(tr, node);
	
	current->parent = current->left = current->right = NULL;
	free(current);
}

tnode_p tree_minimum(tnode_p node){
	while(node->left != NULL)
		node = node->left;
	return node;
}

tnode_p tree_maximum(tnode_p node){
	while(node->right != NULL)
		node = node->right;
	return node;
}

tnode_p tree_predecessor(tnode_p node){
	tnode_p next;

	if(node->left != NULL)
		return tree_maximum(node->left);

	next = node->parent;
		
	while(next != NULL && node == next->left){
		node = next;
		next = next->parent;
	}
	return next;
}

tnode_p tree_successor(tnode_p node){
	tnode_p next;
	
	if(node->right != NULL)
		return tree_minimum(node->right);

	next = node->parent;
		
	while(next != NULL && node == next->right){
		node = next;
		next = next->parent;
	}
	return next;
}

static tnode_p search_r(tnode_p node, treecmpfunc cmpfunc, void * key){
	int res;
	
	if(node == NULL) return NULL;
	
	res = cmpfunc(key, node->data);

	if(res == 0) return node;
	if(res < 0) return search_r(node->left, cmpfunc, key);
	return search_r(node->right, cmpfunc, key);
}

tnode_p tree_search(tree_p tr, void * key){
	return search_r(tr->root, tr->cmpfunc, key);
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

int rb_color(tnode_p node){
	if(node == NULL) return BLACK;
	return node->color;
}

tnode_p rb_insert(tree_p tr, void * data, int size){
	tnode_p node, current, uncle, parent;

	current = node = tree_insert(tr, data, size);
	node->color = RED;

	while(current != tr->root && rb_color(current->parent) == RED){
		parent = current->parent;
		if(parent == parent->parent->left){
			uncle = parent->parent->right;
			if(rb_color(uncle) == RED){
				parent->color = BLACK;
				uncle->color = BLACK;
				current = parent->parent;
				current->color = RED;
			} else if(current == parent->right){
				current = parent;
				left_rotate(tr, current);
			} else {
				parent->color = BLACK;
				parent->parent->color = RED;
				right_rotate(tr, parent->parent);
			}
		} else {
			uncle = parent->parent->left;
			if(rb_color(uncle) == RED){
				parent->color = BLACK;
				uncle->color = BLACK;
				current = parent->parent;
				current->color = RED;
			} else if(current == parent->left){
				current = parent;
				right_rotate(tr, current);
			} else {
				parent->color = BLACK;
				parent->parent->color = RED;
				left_rotate(tr, parent->parent);
			}
		}
	}

	tr->root->color = BLACK;
	
	return node;
}

static void rb_delete_fixup(tree_p tr, tnode_p parent, tnode_p node){
	tnode_p sibling;
	while(node != tr->root && rb_color(node) == BLACK){
		if( node == parent->left ){
			sibling = parent->right;
			if(rb_color(sibling) == RED){
				sibling->color = BLACK;
				parent->color = RED;
				left_rotate(tr, parent);
				sibling = parent->right;
			}

			if(rb_color(sibling->left) == BLACK 
					&& rb_color(sibling->right) == BLACK){
				sibling->color = RED;
				node = parent;
				parent = parent->parent;
			} else if(rb_color(sibling->right) == BLACK){
				sibling->left->color = RED;
				right_rotate(tr, sibling);
				sibling = parent->right;
			} else {
				sibling->color = parent->color;
				parent->color = BLACK;
				sibling->right->color = BLACK;
				left_rotate(tr, parent);
				node = tr->root;
				parent = NULL;
			}
		}
		else{
			sibling = parent->left;
			if(rb_color(sibling) == RED){
				sibling->color = BLACK;
				parent->color = RED;
				right_rotate(tr, parent);
				sibling = parent->left;
			}

			if(rb_color(sibling->left) == BLACK 
					&& rb_color(sibling->right) == BLACK){
				sibling->color = RED;
				node = parent;
				parent = parent->parent;
			} else if(rb_color(sibling->left) == BLACK){
				sibling->right->color = RED;
				left_rotate(tr, sibling);
				sibling = parent->left;
			} else {
				sibling->color = parent->color;
				parent->color = BLACK;
				sibling->left->color = BLACK;
				right_rotate(tr, parent);
				node = tr->root;
				parent = NULL;
			}
		}
	}
	if(node != NULL) node->color = BLACK;
}

void rb_delete(tree_p tr, tnode_p node){
	tnode_p current = pull_out(tr, node);
	tnode_p next;

	if(current->left != NULL)
		next = current->left;
	else next = current->right;

	if(rb_color(current) == BLACK)
		rb_delete_fixup(tr, current->parent, next);

	current->parent = current->left = current->right = NULL;
	free(current);
}
