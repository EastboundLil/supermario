#include "Mario.h"

Mario::Mario() :
    Terrain(Position(100,116), "mario", 64)
{

}

Mario::Mario(int x, int y) :
    Terrain(Position(x,y), "mario", 64)
{

}

void Mario::moveRight()
{
    position.x += horizontalSpeed;
    distance += horizontalSpeed;
    LOG("distance: " << distance);
}

void Mario::moveLeft()
{
    position.x -= horizontalSpeed;
    distance -= horizontalSpeed;
    LOG("distance: " << distance);
}

void Mario::jump()
{
    if(speed == 0) speed = -20;
    position.y--;
}

void Mario::fall(int groundLevel)
{
    groundLevel -= height;
    if(position.y < groundLevel)
    {
        position.y += speed;
        speed += acceleration;
    }
    if(position.y >= groundLevel)
    {
        speed = 0;
        position.y = groundLevel;
    }
}



