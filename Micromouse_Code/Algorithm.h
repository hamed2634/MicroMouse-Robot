#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Control.h"

#define	QUEUE	FIFO
#define STACK LIFO

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

void updateCoordinates(short Direction, short Wall, short x, short y, short &toX, short &toY);
void move(short &Direction, short x, short y, short toX, short toY);
void floodFill(short x, short y, short &Direction);
void BFS(short source, short target, short& Direction);
void doIt();

#endif