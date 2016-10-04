#ifndef FILED_H
#define FIELD_H
#include "List.h"
#include "Cell.h"

typedef struct {
	int size;	
	Cell * cur,
	     * mem;
	Node * alive;
} Field;

int iniField(Field * field, int size);

void freeField(Field * field);

void evolve(Field * field);

#endif
