#include <malloc.h>
#include "Field.h"

/*
   The first bit represent is the cell dead or alive
   The second bit represent if the cell was changed in last step
*/
int iniField(Field * field, int size)
{
	if(size < 1)
		return 1;

	field->cur = (Cell*) malloc(size * size * sizeof(Cell));
	field->mem = (Cell*) malloc(size * size * sizeof(Cell));
	field->size = size;

	for(int i = 0; i < size * size; ++i)
	{
		field->cur[i].state = 2 + (rand() % 2);
		ini_nbs(field->cur, &(field->cur[i]), i, size);
	}
	for(int i = 0; i < size * size; ++i)
		for(int j = 0; j < 8; ++j)
			field->mem[i].nbs[j] = field->cur[i].nbs[j];

	field->alive = create_list();
	for(int i = 1; i < size * size; ++i)
		push_back(field->alive, i);

	return 0;
}

void freeField(Field * field)
{	//maybe should set pointers to zero?
	free(field->cur);
	free(field->mem);
	delete_list( &(field->alive));
}

/* modulo that handles negative numbers */
int mod(int n, int m)
{
	return (((n < 0) ? ((n % m) + m) : n) % m);
}

void ini_nbs(Cell * field, Cell * cell, int pos, int size)
{	// yeah, not very elegant
	int i = pos / size, 
	    j = pos % size;
	int x = mod(i * size - size, size * size),
	    y = mod(j - 1, size);
	cell->nbs[0] = mod(x + y, size * size);
	cell->nbs[1] = mod(x + mod(y + 1, size), size * size);
	cell->nbs[2] = mod(x + mod(y + 2, size), size * size);
	
	x = i * size;
	y = mod(j - 1, size);
	cell->nbs[3] = mod(x + y, size*size);
	cell->nbs[4] = mod(x + mod(y + 2, size), size * size);
	
	x = mod(i * size + size, size * size);
	y = mod(j - 1, size);
	cell->nbs[5] = mod(x + y, size * size);
	cell->nbs[6] = mod(x + mod(y + 1, size), size * size);
	cell->nbs[7] = mod(x + mod(y + 2, size), size * size);
}

int calc_nbs(Cell * field, Cell cell)
{
	int res = 0;
	for(int i = 0; i < 8; ++i)
		res += field[cell.nbs[i]].state & 1;
	return res;
}

int is_dead_area(Cell * field, Cell cell)
{
	for(int i = 0; i < 8; ++i)
		if(field[cell.nbs[i]].state & 2)
			return 0;
	return 1;
}

void evolve(Field * field)
{
	int nbs, i;
	Node * itr = field->alive, * tmp;

	while(itr)
	{
		i = itr->indx;
		nbs = calc_nbs(field->cur, field->cur[i]);
		field->mem[i].state = (field->cur[i].state & 1) ? (nbs == 2 || nbs == 3) : nbs == 3;

		if(field->mem[i].state != (field->cur[i].state & 1))
		{
			field->mem[i].state |= 2;
			for(int n = 0; n < 8; ++n) 
				push_back(field->alive, field->cur[i].nbs[n]);	//very bad
		}
		else
		{
			if(is_dead_area(field->mem, field->cur[i]))
			{
				tmp = itr->next;
				remove_node(&(field->alive), itr);
				itr = tmp;
				continue;
			}	
		}
		itr = itr->next;
	}

	Cell * p = field->cur;
	field->cur = field->mem;
	field->mem = p;
}
