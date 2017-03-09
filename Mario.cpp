#include "Mario.h"

Mario::Mario() :
    Enemy(Position(100,116), "mario", 64, 300, 5)
{
    movingLeft = false;
}

Mario::Mario(int x, int y) :
    Enemy(Position(x,y), "mario", 64, 300,5)
{
    movingLeft = false;
}

void Mario::reset(int x, int y)
{
    setPosition(x,y);
    distance = 300;
}

void Mario::moveRight(int next)
{
    if(next >= position.y + height)
    {
        distance += horizontalSpeed;
    }
    movingLeft = false;
}

void Mario::moveLeft(int prev)
{
    if(prev >= position.y + height)
    {
        distance -= horizontalSpeed;
    }
    movingLeft = true;
}



