#include "Terrain.h"

Terrain::Terrain(Position position, canvas texture) :
    position(position),
    widget(texture)
{

}

Position Terrain::getPosition() const
{
    return position;
}

Widget Terrain::getWidget() const
{
    return widget;
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
