//
// Created by till we find a name on 9/19/2023.
//

#ifndef PROJECT_FLOODFILL_H
#define PROJECT_FLOODFILL_H

#include <queue>

// every bit in represent information

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
void getAvailable(short data, short Direction, short x, short y, bool visited[], short parent[], std::queue<short> &q);
void BFS(short source, short target, short Direction, short data[]);
void doIt();


#endif //PROJECT_FLOODFILL_H
