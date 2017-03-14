#ifndef POSITION_H
#define POSITION_H

struct Position
{
    Position() : x(0), y(0) {}
    Position(double x, double y) : x(x), y(y) {}

    double x;
    double y;
};

#endif // POSITION_H
