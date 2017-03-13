#include "Mario.h"

Mario::Mario() :
    Enemy(Position(100,116), "mario", 0, 93, 300, 5),
    score(0)
{
    movingLeft = false;
    health = 2;
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

void Mario::jump()
{
        if(speed == 0) speed = -20;
        position.y--;
}

