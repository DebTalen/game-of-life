#include <malloc.h>
#include "List.h"

Node * create_list()
{
	Node * head = (Node*) malloc(sizeof(Node));
	head->next = 0;
	head->indx = 0;
	return head;
}

void delete_list(Node ** head)
{
	if(head)
	{	
		Node * iter = (*head);
		Node * tmp = 0;		
		while(iter)
		{
			tmp = iter->next;
			free(iter);
			iter = tmp;
		}
	}
	(*head) = 0;
}

Node * push_back(Node * head, int indx)
{
	Node * itr = head, * tmp;	
	while(itr)
	{
		if(indx == itr->indx)
			return 0;
		tmp = itr;
		itr = itr->next;
	}
	
	tmp->next = (Node*) malloc(sizeof(Node));
	
	itr = tmp->next;
	itr->next = 0;
	itr->indx = indx;
	return itr;
}

Node * find_node(Node * head, int indx)
{
	Node * itr = head;
	while(itr)
	{
		if(itr->indx == indx)
			break;
		itr = itr->next;
	}
	return itr;
}

int remove_node(Node ** head, Node * node)
{
	if(! head)
		return -1;

	
	Node * itr = (*head);
	Node * tmp = 0;
	
	while(itr)
	{
		if(node == itr)
			break;

		tmp = itr;
		itr = itr->next;
	}		
	
	if(! tmp)
	{
		(*head) = itr->next;
		free(itr);
	}
	else
	{
		tmp->next = itr->next;
		free(itr);
	}
	return 0;
}
