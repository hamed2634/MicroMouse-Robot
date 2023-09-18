#ifndef FLOODFILL_H
#define FLOODFILL_H


#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3


#include <vector>
#include <queue>
#include <stack>


void updateCoordinates(short Direction, short Wall, short x, short y, short &toX, short &toY);
void move(short &Direction, short x, short y, short toX, short toY);
void floodFill(short x, short y, short &Direction, bool visited[][17], bool matrix[][257]);
void BFS(short source, short target, short Direction, bool matrix[][257]);
void doIt();

#endif
