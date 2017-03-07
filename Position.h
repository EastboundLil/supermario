#ifndef POSITION_H
#define POSITION_H

struct Position
{
    Position() : x(0), y(0) {}
    Position(int x, int y) : x(x), y(y) {}

    int x;
    int y;
};

#endif // POSITION_H
