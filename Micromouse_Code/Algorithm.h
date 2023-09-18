#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Control.h"

#define	IMPLEMENTATION	FIFO

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

void updateCoordinates(short Direction, short Wall, short x, short y, short &toX, short &toY);
void move(short &Direction, short x, short y, short toX, short toY);
void floodFill(short x, short y, short &Direction, bool visited[][17], bool matrix[][257]);
void BFS(short source, short target, short Direction, bool matrix[][257]);
void doIt();

#endif