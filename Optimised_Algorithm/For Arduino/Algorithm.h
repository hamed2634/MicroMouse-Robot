#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Control.h"

#define	QUEUE	FIFO
#define STACK LIFO

#define NORTH 1
#define SOUTH 2
#define EAST 4
#define WEST 16


#define FRONT 32
#define BACK 64
#define RIGHT 128
#define LEFT 256


void move(short &Direction, short x, short y, short toX, short toY);
void updateCoordinates(short Direction, short Wall, short x, short y, short &toX, short &toY);
void floodFill(short x, short y, short &Direction, bool visited[][17], short data[]);
short getDirection(short data);
void getAvailable(short data, short Direction, short x, short y, bool visited[], short depth[], short parent[], cppQueue q);
void BFS(short source, short target, short Direction, short data[]);
void doIt();

#endif