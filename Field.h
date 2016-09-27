#ifndef FILED_H
#define FIELD_H
#include "List.h"

//typedef unsigned short ushort;

typedef struct {
	int size;	//size x size
	char ** cur,
	     ** mem;
	Node * alive;
} Field;

int iniField(Field * field, int size);

void freeField(Field * field);

void evolve(Field * field);

#endif
