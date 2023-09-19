#include "Algorithm.h"
bool visited[17][17];
short matrix[257][1];

void move(short &Direction, short x, short y, short toX, short toY) {
    if (toX == x) {
        if (y > toY) {
            switch (Direction) {
                case NORTH:
                    TurnLeft(), MoveCellForward();
                    break;
                case SOUTH:
                    TurnRight(), MoveCellForward();
                    break;
                case WEST:
                    MoveCellForward();
                    break;
                case EAST:
                    TurnRight(), TurnRight(), MoveCellForward();
                    break;
                default:

                    break;
            }
            Direction = WEST;
        }
        else {
            switch (Direction) {
                case NORTH:
                    TurnRight(), MoveCellForward();
                    break;
                case SOUTH:
                    TurnLeft(), MoveCellForward();
                    break;
                case WEST:
                    TurnRight(), TurnRight(), MoveCellForward();
                    break;
                case EAST:
                    MoveCellForward();
                    break;
                default:

                    break;
            }
            Direction = EAST;
        }
    }
    else if (x > toX) {
        switch (Direction) {
            case NORTH:
                MoveCellForward();
                break;
            case SOUTH:
                TurnRight(), TurnRight(), MoveCellForward();
                break;
            case WEST:
                TurnRight(), MoveCellForward();
                break;
            case EAST:
                TurnLeft(), MoveCellForward();
                break;
            default:

                break;
        }
        Direction = NORTH;
    }
    else {
        switch (Direction) {
            case NORTH:
                TurnRight(), TurnRight(), MoveCellForward();
                break;
            case SOUTH:
                MoveCellForward();
                break;
            case WEST:
                TurnLeft(), MoveCellForward();
                break;
            case EAST:
                TurnRight(), MoveCellForward();
                break;
            default:

                break;
        }
        Direction = SOUTH;
    }
}


void updateCoordinates(short Direction, short Wall, short x, short y, short &toX, short &toY) {
    if (Wall == 1) {
        switch (Direction) {
            case NORTH:
                toX = --x, toY = y;
                return;
            case SOUTH:
                toX = ++x, toY = y;
                return;
            case WEST:
                toX = x, toY = --y;
                return;
            case EAST:
                toX = x, toY = ++y;
                return;
            default:

                break;
        }
    }
    else if (Wall == 2) {
        switch (Direction) {
            case NORTH:
                toX = x, toY = ++y;
                return;
            case SOUTH:
                toX = x, toY = --y;
                return;
            case WEST:
                toX = --x, toY = y;
                return;
            case EAST:
                toX = ++x, toY = y;
                return;
            default:

                break;
        }
    }
    else {
        switch (Direction) {
            case NORTH:
                toX = x, toY = --y;
                return;
            case SOUTH:
                toX = x, toY = ++y;
                return;
            case WEST:
                toX = ++x, toY = y;
                return;
            case EAST:
                toX = --x, toY = y;
                return;
            default:
                break;
        }
    }
}


void floodFill(short x, short y, short &Direction) {
    visited[x][y] = true;

    short toX, toY, a, b;

    if (! wallFront()) {
        updateCoordinates(Direction, 1, x, y, toX, toY);

        a = (short) ( (x - 1) * 16 + y );
        b = (short) ( (toX - 1) * 16 + toY );
        matrix[a][b] = matrix[b][a] = true;

        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction);
            move(Direction, toX, toY, x, y);
        }
    }

    if (! wallRight()) {
        updateCoordinates(Direction, 2, x, y, toX, toY);

        a = (short) ( (x - 1) * 16 + y );
        b = (short) ( (toX - 1) * 16 + toY );
        matrix[a][b] = matrix[b][a] = true;

        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction);
            move(Direction, toX, toY, x, y);
        }
    }

    if (! wallLeft()) {
        updateCoordinates(Direction, 3, x, y, toX, toY);

        a = (short) ( (x - 1) * 16 + y );
        b = (short) ( (toX - 1) * 16 + toY );
        matrix[a][b] = matrix[b][a] = true;

        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction);
            move(Direction, toX, toY, x, y);
        }
    }

    if (! wallFront()) {
        updateCoordinates(Direction, 1, x, y, toX, toY);

        a = (short) ( (x - 1) * 16 + y );
        b = (short) ( (toX - 1) * 16 + toY );
        matrix[a][b] = matrix[b][a] = true;

        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction);
            move(Direction, toX, toY, x, y);
        }
    }

    if (! wallRight()) {
        updateCoordinates(Direction, 2, x, y, toX, toY);

        a = (short) ( (x - 1) * 16 + y );
        b = (short) ( (toX - 1) * 16 + toY );
        matrix[a][b] = matrix[b][a] = true;

        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction);
            move(Direction, toX, toY, x, y);
        }
    }

    if (! wallLeft()) {
        updateCoordinates(Direction, 3, x, y, toX, toY);

        a = (short) ( (x - 1) * 16 + y );
        b = (short) ( (toX - 1) * 16 + toY );
        matrix[a][b] = matrix[b][a] = true;

        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction);
            move(Direction, toX, toY, x, y);
        }
    }

}


void BFS(short source, short target,short & Direction) {
    short n = 257;

    cppQueue	q(sizeof(int), 255, QUEUE);	// Instantiate queue

    short depth[n], parent[n];
    for (short i = 0; i < n; ++i) {
        depth[i] = parent[i] = -1;
    }

    q.push(&source);
    parent[source] = -1;
    depth[source] = 0;

    for (short d = 0, length = (short) q.sizeOf(); ! q.isEmpty() && depth[target] == -1; ++d, length = (short) q.sizeOf()) {
        while (length-- && depth[target] == -1) {
            short p; q.pop(&p);

            for (short c = 1; c < n; ++c) {
                if (matrix[p][c]) {
                    if (depth[c] == -1) {
                        q.push(&c);
                        depth[c] = (short) (d + 1);
                        parent[c] = p;
                    }
                }

                if (depth[target] != -1)
                    break;
            }

        }
    }

    cppQueue path(sizeof(int), 255, STACK);	// Instantiate Stack


    for (short current = target; parent[current] != -1; current = parent[current])
        path.push(&current);

    short x = 16, y = 1, a, b;
    while (! path.isEmpty()) {
        short top;
        path.pop(&top);

        a = (short) ( (top + 15) / 16 );
        b = (short) ( top % 16 );

        if (! b)
            b = 16;

        move(Direction, x, y, a, b);

        x = a, y = b;
    }
}


void doIt() {
    short Direction = NORTH;

    for (short i = 1; i < 17; ++i) {
        for (short j = 1; j < 17; ++j) {
            visited[i][j] = false;
        }
    }
    for (short i = 0; i < 257; ++i) {
        for (short j = 0; j < 4; ++j) {
            matrix[i][j] = false;
        }
    }
    floodFill(16, 1, Direction);
    BFS(241, 120, Direction);
}
