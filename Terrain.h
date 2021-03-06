#ifndef TERRAIN_H
#define TERRAIN_H

#include "Position.h"
#include "graphics.hpp"
#include "Widget.h"

using namespace genv;

class Terrain
{
public:
    Terrain(Position position, std::string type, int height);
    Position getPosition() const {return position;}
    std::string getType() const {return type;}

    void setPosition(int x, int y);
    void setPosition(Position pos);
    virtual int getHeight() {return height;}

    virtual ~Terrain() {}
protected:
    Position position;
    std::string type;
    int height;

};

#endif // TERRAIN_H
