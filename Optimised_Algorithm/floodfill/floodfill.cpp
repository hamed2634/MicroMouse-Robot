//
// Created by till we find a name on 9/19/2023.
//

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
                return;
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
                return;
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
                return;
        }
    }
}


void floodFill(short x, short y, short &Direction, bool visited[][17], short data[]) {
    visited[x][y] = true;

    short node = (short) ( (x - 1) * 16 + y );

    data[node] = (short) (data[node] | Direction);

    data[node] |= BACK;
    if (! API::wallFront()) {
        data[node] |= FRONT;
    }
    if (! API::wallRight()) {
        data[node] |= RIGHT;
    }
    if (! API::wallLeft()) {
        data[node] |= LEFT;
    }

    short toX, toY;

    if (! API::wallFront()) {
        updateCoordinates(Direction, 1, x, y, toX, toY);
        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction, visited, data);
            move(Direction, toX, toY, x, y);
        }
    }

    if (! API::wallRight()) {
        updateCoordinates(Direction, 2, x, y, toX, toY);
        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction, visited, data);
            move(Direction, toX, toY, x, y);
        }
    }

    if (! API::wallLeft()) {
        updateCoordinates(Direction, 3, x, y, toX, toY);
        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction, visited, data);
            move(Direction, toX, toY, x, y);
        }
    }

    if (! API::wallFront()) {
        updateCoordinates(Direction, 1, x, y, toX, toY);
        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction, visited, data);
            move(Direction, toX, toY, x, y);
        }
    }

    if (! API::wallRight()) {
        updateCoordinates(Direction, 2, x, y, toX, toY);
        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction, visited, data);
            move(Direction, toX, toY, x, y);
        }
    }

    if (! API::wallLeft()) {
        updateCoordinates(Direction, 3, x, y, toX, toY);
        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction, visited, data);
            move(Direction, toX, toY, x, y);
        }
    }

    if (! API::wallFront()) {
        updateCoordinates(Direction, 1, x, y, toX, toY);
        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction, visited, data);
            move(Direction, toX, toY, x, y);
        }
    }

    if (! API::wallRight()) {
        updateCoordinates(Direction, 2, x, y, toX, toY);
        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction, visited, data);
            move(Direction, toX, toY, x, y);
        }
    }

    if (! API::wallLeft()) {
        updateCoordinates(Direction, 3, x, y, toX, toY);
        if (! visited[toX][toY]) {
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction, visited, data);
            move(Direction, toX, toY, x, y);
        }
    }
}


short getDirection(short data) {
    if (data & NORTH) {
        return NORTH;
    }
    else if (data & SOUTH) {
        return SOUTH;
    }
    else if (data & WEST) {
        return WEST;
    }
    else {
        return EAST;
    }
}


void getAvailable(short data, short Direction, short x, short y, bool visited[], short depth[], short parent[], std::queue<short> &q) {
    short from = (x - 1) * 16 + y;

    short to, toX, toY;

    if (data & FRONT) {
        switch (Direction) {
            case NORTH:
                toX = x - 1, toY = y;
                break;
            case SOUTH:
                toX = x + 1, toY = y;
                break;
            case WEST:
                toX = x, toY = y - 1;
                break;
            case EAST:
                toX = x, toY = y + 1;
                break;
            default:
                break;
        }
        to = (toX - 1) * 16 + toY;
        if (depth[to] == -1) {
            q.push(to);
            parent[to] = from;
            depth[to] = depth[from] + 1;
        }
    }

    if (data & BACK) {
        switch (Direction) {
            case NORTH:
                toX = x + 1, toY = y;
                break;
            case SOUTH:
                toX = x - 1, toY = y;
                break;
            case WEST:
                toX = x, toY = y + 1;
                break;
            case EAST:
                toX = x, toY = y - 1;
                break;
            default:
                break;
        }
        to = (toX - 1) * 16 + toY;
        if (depth[to] == -1) {
            q.push(to);
            parent[to] = from;
            depth[to] = depth[from] + 1;
        }
    }

    if (data & RIGHT) {
        switch (Direction) {
            case NORTH:
                toX = x, toY = y + 1;
                break;
            case SOUTH:
                toX = x, toY = y - 1;
                break;
            case WEST:
                toX = x - 1, toY = y;
                break;
            case EAST:
                toX = x + 1, toY = y;
                break;
            default:
                break;
        }
        to = (toX - 1) * 16 + toY;
        if (depth[to] == -1) {
            q.push(to);
            parent[to] = from;
            depth[to] = depth[from] + 1;
        }
    }

    if (data & LEFT) {
        switch (Direction) {
            case NORTH:
                toX = x, toY = y - 1;
                break;
            case SOUTH:
                toX = x, toY = y + 1;
                break;
            case WEST:
                toX = x + 1, toY = y;
                break;
            case EAST:
                toX = x - 1, toY = y;
                break;
            default:
                break;
        }
        to = (toX - 1) * 16 + toY;
        if (depth[to] == -1) {
            q.push(to);
            parent[to] = from;
            depth[to] = depth[from] + 1;
        }
    }
}


void BFS(short source, short target, short Direction, short data[]) {
    std::queue<short> q;

    bool visited[257];
    short depth[257], parent[257];
    for (short i = 0; i < 257; ++i) {
        visited[i] = false;
    }
    for (short i = 0; i < 257; ++i) {
        depth[i] = parent[i] = -1;
    }

    q.push(source);
    depth[source] = 0;
    visited[source] = true;

    for (short d = 0, length = (short) q.size(), a, b; ! q.empty() && depth[target] == -1; ++d, length = (short) q.size()) {
        while (length-- && depth[target] == -1) {
            short p = q.front();
            q.pop();

            a = (short) ( (p + 15) / 16 );
            b = (short) ( p % 16 );

            if (! b) {
                b = 16;
            }

            getAvailable(data[p], getDirection(data[p]), a, b, visited, depth, parent, q);
        }
    }

    std::stack<short> path;

    for (short current = target; parent[current] != -1; current = parent[current])
        path.push(current);

    short x = 16, y = 1, a, b;
    while (! path.empty()) {
        a = (short) ( (path.top() + 15) / 16 );
        b = (short) ( path.top() % 16 );

        if (! b) {
            b = 16;
        }

        move(Direction, x, y, a, b);

        x = a, y = b;
        path.pop();
    }
}


void doIt() {
    short Direction = NORTH;
    bool visited[17][17];
    short data[257];

    for (short i = 0; i < 17; ++i) {
        for (short j = 0; j < 17; ++j) {
            visited[i][j] = false;
        }
    }
    for (short i = 0; i < 257; ++i) {
        data[i] = 0;
    }

    floodFill(16, 1, Direction, visited, data);
    BFS(241, 120, Direction, data);
}

