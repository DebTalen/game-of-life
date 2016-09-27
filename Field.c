#include <malloc.h>
#include "Field.h"

int iniField(Field * field, int size)
{
	if(size < 1)
		return 1;

	if(create_list(&(field->alive)))
		return 2;

	field->cur = (char**) malloc(size * sizeof(char*));
	field->mem = (char**) malloc(size * sizeof(char*));
	for(int i = 0; i < size; ++i)
	{
		field->cur[i] = (char*) malloc(size * sizeof(char));
		field->mem[i] = (char*) malloc(size * sizeof(char));
	}

	for(int i = 0; i < size; ++i)
		for(int j = 0; j < size; ++j)
			field->cur[i][j] = rand()% 2;

//	blinker	
//	field->cur[1][1] = 1; 
//	field->cur[2][1] = 1; 
//	field->cur[3][1] = 1; 


	for(int i = 1; i < size * size; ++i)
		push_back(field->alive, i);

	field->size = size;
	return 0;
}

void freeField(Field * field)
{
	for(int i = 0; i < field->size; ++i)
	{
		free(field->cur[i]);
		free(field->mem[i]);
	}
	free(field->cur);
	free(field->mem);
	delete_list( &(field->alive));
}

int calc_neighboor(char ** arr, int x, int y, int size)
{
	if(--x < 0) x += size;
	if(--y < 0) y += size;
	int res = 0, temp = y;

	for(int i = 0; i < 3; ++i, x = (++x) % size, y = temp)
		for(int j = 0; j < 3; ++j, y = (++y) % size)
		{
			if(i == 1 && j == 1)
				continue;
			res += arr[x][y];
		}
	return res;
}

void mark_nbh(Node * head, int x, int y, int size)
{
	if(--x < 0) x += size;
	if(--y < 0) y += size;
	int temp = y;

	for(int i = 0; i < 3; ++i, x = (++x) % size, y = temp)
		for(int j = 0; j < 3; ++j, y = (++y) % size)
			push_back(head, (x + y));
}

void evolve(Field * field)
{	//Work very krivo
	char nbh, i = 0, j = 0;
	Node * itr = field->alive, *tmp;
	while(itr->next)
	{
		i = itr->indx / field->size;
		j = itr->indx % field->size;

		nbh = calc_neighboor(field->cur, i, j, field->size);
		
		if(field->cur[i][j]) 
		{
			if(nbh == 2 || nbh == 3)
				field->mem[i][j] = 1;
			else
				field->mem[i][j] = 0;
		}
		else 
		{
			if(nbh == 3){
				field->mem[i][j] = 1;}
			else {
				field->mem[i][j] = 0;} //?????
		}
	
		if(field->cur[i][j] == field->mem[i][j]) //	????/????
		{
			mark_nbh(field->alive, i, j, field->size);	
			itr = itr->next;
		}
		else
		{
			tmp = itr->next;
			remove_node(field->alive, itr);
			itr = tmp;
		}			
	}

	char ** p = field->cur;
	field->cur = field->mem;
	field->mem = p;
}
