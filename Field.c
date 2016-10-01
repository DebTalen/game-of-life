#include <malloc.h>
#include "Field.h"

int iniField(Field * field, int size)
{
	if(size < 1)
		return 1;

	field->alive = create_list();

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

//	toad
/*	field->cur[1][1] = 1;
	field->cur[1][2] = 1;
	field->cur[1][3] = 1;
	field->cur[2][0] = 1;
	field->cur[2][1] = 1;
	field->cur[2][2] = 1; */

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

int calc_nbh(char ** arr, int x, int y, int size)
{
	if(--x < 0) x += size;
	if(--y < 0) y += size;
	int res = 0, temp = y;

	for(int i = 0; i < 3; ++i, x = (++x) % size, y = temp)
	{
		for(int j = 0; j < 3; ++j, y = (++y) % size)
		{
			if(i == 1 && j == 1)
				continue;
			res += arr[x][y];
		}
	}
	return res;
}

/*int is_dead_area(Field * field, int x, int y)
{
	int size = field->size, temp;
	if(--x < 0) x += size;
	if(--y < 0) y += size;
	temp = y;

	for(int i = 0; i < 3; ++i, x = (++x) % size, y = temp)
	{
		for(int j = 0; j < 3; ++j, y = (++y) % size)
		{
			if(field->cur[x][y] != field->mem[x][y])
				return 0;
		}
	}
	return 1;
}*/

void evolve(Field * field)
{	
	char nbh, i = 0, j = 0;
	Node * itr = field->alive;

	for(int i = 0; i < field->size; ++i)
	{
		for(int j = 0; j < field->size; ++j)
		{
			nbh = calc_nbh(field->cur, i, j, field->size);
			field->mem[i][j] = field->cur[i][j] ? (nbh == 2 || nbh == 3) : nbh == 3;	
		}
	}

/*	For future improvements
	while(itr)
	{
		i = itr->indx / field->size;
		j = itr->indx % field->size;

		nbh = calc_nbh(field->cur, i, j, field->size);
		field->mem[i][j] = field->cur[i][j] ? (nbh == 2 || nbh == 3) : nbh == 3;

		if(is_dead_area(field, i, j))
		{
			there must be some optimization staff
		}

		itr = itr->next;
	}
*/
	char ** p = field->cur;
	field->cur = field->mem;
	field->mem = p;
}
