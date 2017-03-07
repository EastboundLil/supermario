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
    Terrain(Position position, std::string type);
    Position getPosition() const;
    Widget getWidget() const;

    void setPosition(int x, int y);
    void setPosition(Position pos);

private:
    Position position;

    Widget widget;
};

#endif // TERRAIN_H
