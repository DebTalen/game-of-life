#ifndef CELL_H
#define CELL_H

typedef struct _cell {
	int state;
	int nbs[8];
} Cell;

#endif 
