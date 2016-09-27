#include <malloc.h>
#include "List.h"

int create_list(Node ** head)
{
//	if(head)
//		return -1;
	*head = (Node*) malloc(sizeof(Node));
	if(! head)
		return -2;
	(*head)->next = 0;
	(*head)->indx = 0;
	return 0;
}

void delete_list(Node ** head)
{
	if(head)
	{	
		Node * iter = head;
		Node * tmp = 0;
		while(iter)
		{
			tmp = iter->next;
			free(iter);
			iter = tmp;
		}
	}
}

int push_back(Node * head, int indx)
{
	Node * iter = head;
	while(iter->next)
	{
		if(iter->indx == indx)
			return -1;
		iter = iter->next;
	}
	
	iter->next = (Node*) malloc(sizeof(Node));
	if(! iter->next)
		return -2;
	
	iter = iter->next;
	iter->next = 0;
	iter->indx = indx;
	return 1;
}

int remove_node(Node ** head, Node * node)
{
	if(! head)
		return -1;

	
	Node * iter = head;
	Node * tmp = 0;
	
	if(node == head)
	{	//?????
		head = (*head)->next;
		free(iter);
		return 0;
	}

	while(iter->next)
	{	//if the next node is what we are looking for
		if(node == iter->next)
		{
			tmp = iter;
			break;
		}
		iter = iter->next;
	}		
	
	if(! tmp)
		return -2;
	
	iter = iter->next;	// node that need to be removed
	tmp->next = iter->next;	// == tmp->next->next;
	free(iter);
	return 0;
}
