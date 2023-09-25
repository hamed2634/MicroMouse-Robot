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

    // give the cell its ID node
    short node = (short) ( (x - 1) * 16 + y );

    // assign the direction entered the cell with to save the state as we need it later
    data[node] = (short) (data[node] | Direction);

    // assign open walls for the cell
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

    /* We ask the SAME question many time because when the car comes back to the cell
     * it may have different direction so the direction of the walls change */

    if (! API::wallFront()) {
        // get the coordinates that we are going to
        updateCoordinates(Direction, 1, x, y, toX, toY);
        if (! visited[toX][toY]) {
            // the move function is just an implementation to move from cell to cell with different directions
            move(Direction, x, y, toX, toY);
            floodFill(toX, toY, Direction, visited, data);
            // to come back == the return.
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


void getAvailable(short data, short Direction, short x, short y, bool visited[], short parent[], std::queue<short> &q) {
    short from = (x - 1) * 16 + y;

    short to, toX = 0, toY = 0;
	
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
        if (!visited[to]) {
            q.push(to);
            parent[to] = from;
			visited[to] = 1;
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
        if (!visited[to]) {
            q.push(to);
            parent[to] = from;
			visited[to] = 1;
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
        if (!visited[to]) {
            q.push(to);
            parent[to] = from;
			visited[to] = 1;
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
        if (!visited[to]) {
            q.push(to);
            parent[to] = from;
			visited[to] = 1;
        }
    }
}


void BFS(short source, short target, short Direction, short data[]) {
    std::queue<short> q;

    bool visited[257];
    short parent[257];
    for (short i = 0; i < 257; ++i) {
        visited[i] = false;
    }
    for (short i = 0; i < 257; ++i) {
        parent[i] = -1;
    }

    q.push(source);
    visited[source] = true;

    for (short d = 0, length = (short) q.size(), a, b; ! q.empty(); ++d, length = (short) q.size()) {
        while (length--) {
            short p = q.front();
            q.pop();

            a = (short) ( (p + 15) / 16 );
            b = (short) ( p % 16 );

            if (! b) {
                b = 16;
            }

            getAvailable(data[p], getDirection(data[p]), a, b, visited, parent, q);
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
    // initial direction.
    short Direction = NORTH;
    // to check the visited cells while discovering the maze in the floodfill
    bool visited[17][17];
    /* store the STATE of every cell in the maze
     * I mean by the state the direction it entered the cell with and the open walls */
    short data[257];

    for (short i = 0; i < 17; ++i) {
        for (short j = 0; j < 17; ++j) {
            visited[i][j] = false;
        }
    }
    for (short i = 0; i < 257; ++i) {
        data[i] = 0;
    }

    // explore the maze
    floodFill(16, 1, Direction, visited, data);

    /* Exception that behind the car exist a wall
     * as we assumed through the code that there is always a path behind the car as we came from behind */
    data[241] = (data[241] & (~BACK));
    BFS(241, 120, Direction, data);
}

