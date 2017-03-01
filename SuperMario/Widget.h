#ifndef WIDGET_H
#define WIDGET_H

#include "graphics.hpp"
#include "Color.h"
#include "Logger.h"

using namespace genv;

class Widget
{
public:
    Widget(int width, int height, Color col)
    {
        c.open(width+1,height+1);
        c << move_to(0,0) << color(col.r,col.g,col.b) << box(width,height);
        LOG("Widget created (" << width << ", " << height << ", " << col.r << ":" << col.g << ":"<< col.b << ")");
    }
    Widget(canvas texture)
    {
        c = texture;
    }

    canvas& getCanvas() { return c; }

private:
    canvas c;
};

#endif // WIDGET_H
