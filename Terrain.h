#ifndef TERRAIN_H
#define TERRAIN_H

#include "Color.h"
#include "Position.h"
#include "graphics.hpp"
#include "Widget.h"

using namespace genv;

class Terrain
{
public:
    Terrain(Position position, std::string type, int height);
    Position getPosition() const;
    Widget getWidget() const;

    void setPosition(int x, int y);
    void setPosition(Position pos);
    int getHeight() { return height;}

protected:
    Position position;
    Widget widget;
    int height;

};

#endif // TERRAIN_H
