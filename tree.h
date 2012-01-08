#ifndef __LIBDS_TREE_H__
#define __LIBDS_TREE_H__

#include <stdlib.h>

enum {
	RED,
	BLACK
};

typedef int (*treecmpfunc)(void*,void*);

struct tree_node {
	struct tree_node * left;
	struct tree_node * right;
	struct tree_node * parent;
	void * data;
	int color;
};

typedef struct tree_node * tnode_p;

tnode_p make_node(void*, int);

struct tree {
	tnode_p root;
	treecmpfunc cmpfunc;
};

typedef struct tree * tree_p;
typedef int (*searchfunc)(void*);

void tree_insert(tree_p tr, void * data, int size);
void tree_delete(tree_p tr, tnode_p node);
void left_rotate(tree_p tr, tnode_p node);
void right_rotate(tree_p tr, tnode_p node);
tnode_p tree_successor(tnode_p node);
tnode_p recursive_search(tree_p tr, searchfunc sfunc);
void destroy_node(tnode_p node);

#endif
