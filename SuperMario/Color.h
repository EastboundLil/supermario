#ifndef COLOR_H
#define COLOR_H

struct Color
{
    Color() : r(0), g(0), b(0) {};
    Color(int r, int g, int b) : r(r), g(g), b(b) {};

    int r;
    int g;
    int b;
};

#endif // COLOR_H
