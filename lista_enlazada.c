#include<stdlib.h>
#include<stdbool.h>

typedef struct DLLNODE {
	void *value;
	struct DLLNODE *prev, *next;
} dllnode;

typedef struct {
	node *start;
} dllist;

dllnode* create_dllnode() {
	return calloc(1, sizeof(dllnode));
}

dllnode* next_dllnode(dllnode *node) {
	return node->next;
}

dllnode* prev_dllnode(dllnode *node) {
	return node->prev;
}

void* access_dllnode(dllnode *node) {
	return node->value;
}

void set_dllnode(dllnode *node, void *value) {
	node->value = value;
}

void link_dllnode(dllnode *node_a, dllnode *node_b) {
	if (node_a) node_a->next = node_b;
	if (node_b) node_b->prev = node_a;
}

void pop_dllnode(dllnode *node) {
	link_dllnode(node->prev, node->next);
	free(node);
}

dllist* create_dllist() {
	return calloc(1, sizeof(dllist));
}

dllnode* access_dllist(dllist *list) {
	return list->start;
}

void set_dllist(dllist *list, dllnode *start) {
	list->start = start;
}

bool empty_dllist(dllist *list) {
	return access_dllist(list) == 0;
}

dllist* create_dllist(size_t n) {
	dllist *list = create_dllist();
	if (!n) return list;
	--n;
	dllnode *node = create_dllnode();
	set_dllist(list, node);
	while (n) {
		link_dllnode(node, create_dllnode());
		node = next_dllnode(node);
	}
	return list;
}

void for_dllist(dllist *list, void (*func)(dllnode *)) {
	if (empty_dllist(list)) return;
	dllnode *node = access_dllist(list);
	dllnode *first = node;
	while (prev_dllnode(node) && !(prev_dllnode(node) != node)) {
	}
	// TODO
}

void clean_dllist(dllist *list) {
	dllnode *node = access_dllist(list), *prev, *next;
	prev = prev_dllnode(node);
	while (node) {
		dllnode *next = next_dllnode(node);
		pop_dllnode(node);
		node = next;
	}
	node = prev;
	while (node) {
		dllnode prev = prev_dllnode(node);
		pop_dllnode(node);
		node = prev;
	}
	set_dllist(list, 0);
}

void pop_dllist(dllist *list, dllnode *node) {
	if (access_dllist(list) == node) {
		if (prev_dllnode(node)) set_dllist(list, prev_dllnode(node));
		else set_dllist(list, next_dllnode(node));
	}
	pop_dllnode(node);
}
