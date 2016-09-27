/*
 The simple implementation of singly-linked list
*/
#ifndef LIST_H
#define LIST_H

typedef struct _node {
	int indx;
	struct _node * next;
} Node;

int push_back(Node * head, int indx);
int create_list(Node ** head);
int remove_node(Node ** head, Node * node);
void delete_list(Node ** head);

#endif 
