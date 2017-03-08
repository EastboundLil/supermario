#include "Terrain.h"

Terrain::Terrain(Position position, std::string type, int height) :
    position(position),
    type(type),
    height(height)
{

}

void Terrain::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}

void Terrain::setPosition(Position pos)
{
    position = pos;
}
