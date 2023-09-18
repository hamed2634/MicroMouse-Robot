#include <queue>
#include <stack>
#include "../API/API.h"
#include "floodfill.h"


void move(short &Direction, short x, short y, short toX, short toY) {
    if (toX == x) {
        if (y > toY) {
            switch (Direction) {
                case NORTH:
                    API::turnLeft(), API::moveForward();
                    break;
                case SOUTH:
                    API::turnRight(), API::moveForward();
                    break;
                case WEST:
                    API::moveForward();
                    break;
                case EAST:
                    API::turnRight(), API::turnRight(), API::moveForward();
                    break;
                default:

                    break;
            }
            Direction = WEST;
        }
        else {
            switch (Direction) {
                case NORTH:
                    API::turnRight(), API::moveForward();
                    break;
                case SOUTH:
                    API::turnLeft(),API:: moveForward();
                    break;
                case WEST:
                    API::turnRight(), API::turnRight(), API::moveForward();
                    break;
                case EAST:
                    API::moveForward();
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
                API::moveForward();
                break;
            case SOUTH:
                API::turnRight(), API::turnRight(), API::moveForward();
                break;
            case WEST:
                API::turnRight(), API::moveForward();
                break;
            case EAST:
                API::turnLeft(), API::moveForward();
                break;
            default:

                break;
        }
        Direction = NORTH;
    }
    else {
        switch (Direction) {
            case NORTH:
                API::turnRight(), API::turnRight(), API::moveForward();
                break;
            case SOUTH:
                API::moveForward();
                break;
            case WEST:
                API::turnLeft(), API::moveForward();
                break;
            case EAST:
                API::turnRight(), API::moveForward();
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


void floodFill(short x, short y, short &Direction, bool visited[][17], bool matrix[][257]) {
    visited[x][y] = true;

    short toX, toY, a, b;

    if (! API::wallFront()) {
        updateCoordinates(Direction, 1, x, y, toX, toY);

        a = (short) ( (x - 1) * 16 + y );
        b = (short) ( (toX - 1) * 16 + toY );
        matrix[a][b] = matrix[b][a] = true;

        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction, visited, matrix);
            move(Direction, toX, toY, x, y);
        }
    }

    if (! API::wallRight()) {
        updateCoordinates(Direction, 2, x, y, toX, toY);

        a = (short) ( (x - 1) * 16 + y );
        b = (short) ( (toX - 1) * 16 + toY );
        matrix[a][b] = matrix[b][a] = true;

        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction, visited, matrix);
            move(Direction, toX, toY, x, y);
        }
    }

    if (! API::wallLeft()) {
        updateCoordinates(Direction, 3, x, y, toX, toY);

        a = (short) ( (x - 1) * 16 + y );
        b = (short) ( (toX - 1) * 16 + toY );
        matrix[a][b] = matrix[b][a] = true;

        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction, visited, matrix);
            move(Direction, toX, toY, x, y);
        }
    }

    if (! API::wallFront()) {
        updateCoordinates(Direction, 1, x, y, toX, toY);

        a = (short) ( (x - 1) * 16 + y );
        b = (short) ( (toX - 1) * 16 + toY );
        matrix[a][b] = matrix[b][a] = true;

        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction, visited, matrix);
            move(Direction, toX, toY, x, y);
        }
    }

    if (! API::wallRight()) {
        updateCoordinates(Direction, 2, x, y, toX, toY);

        a = (short) ( (x - 1) * 16 + y );
        b = (short) ( (toX - 1) * 16 + toY );
        matrix[a][b] = matrix[b][a] = true;

        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction, visited, matrix);
            move(Direction, toX, toY, x, y);
        }
    }

    if (! API::wallLeft()) {
        updateCoordinates(Direction, 3, x, y, toX, toY);

        a = (short) ( (x - 1) * 16 + y );
        b = (short) ( (toX - 1) * 16 + toY );
        matrix[a][b] = matrix[b][a] = true;

        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction, visited, matrix);
            move(Direction, toX, toY, x, y);
        }
    }
}


void BFS(short source, short target, short Direction, bool matrix[][257]) {
    short n = 257;

    std::queue<short> q;

    short depth[n], parent[n];
    for (short i = 0; i < n; ++i) {
        depth[i] = parent[i] = -1;
    }

    q.push(source);
    parent[source] = -1;
    depth[source] = 0;

    for (short d = 0, length = (short) q.size(); ! q.empty() && depth[target] == -1; ++d, length = (short) q.size()) {
        while (length-- && depth[target] == -1) {
            short p = q.front();
            q.pop();

            for (short c = 1; c < n; ++c) {
                if (matrix[p][c]) {
                    if (depth[c] == -1) {
                        q.push(c);
                        depth[c] = (short) (d + 1);
                        parent[c] = p;
                    }
                }

                if (depth[target] != -1)
                    break;
            }
        }
    }

    std::stack<short> path;

    for (short current = target; parent[current] != -1; current = parent[current])
        path.push(current);

    short x = 16, y = 1, a, b;
    while (! path.empty()) {
        a = (short) ( (path.top() + 15) / 16 );
        b = (short) ( path.top() % 16 );

        if (! b)
            b = 16;

        move(Direction, x, y, a, b);

        x = a, y = b;
        path.pop();
    }
}


void doIt() {
    short Direction = NORTH;
    bool visited[17][17], matrix[257][257];

    for (short i = 1; i < 17; ++i) {
        for (short j = 1; j < 17; ++j) {
            visited[i][j] = false;
        }
    }
    for (short i = 0; i < 257; ++i) {
        for (short j = 0; j < 257; ++j) {
            matrix[i][j] = false;
        }
    }
    floodFill(16, 1, Direction, visited, matrix);
    BFS(241, 120, Direction, matrix);
}

