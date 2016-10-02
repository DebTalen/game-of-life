/*
 The simple implementation of singly-linked list
*/
#ifndef LIST_H
#define LIST_H

typedef struct _node {
	int indx;
	int nbs[8];	
	struct _node * next;
} Node;

Node * create_list();
Node * find_node(Node * head, int indx);
int push_back(Node * head, int indx);
int remove_node(Node ** head, Node * node);
void delete_list(Node ** head);

#endif 
