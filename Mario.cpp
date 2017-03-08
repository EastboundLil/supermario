#include "Mario.h"

Mario::Mario() :
    Enemy(Position(100,116), "mario", 64, 300, 5)
{

}

Mario::Mario(int x, int y) :
    Enemy(Position(x,y), "mario", 64, 300, 5)
{
    distance = 300;
    horizontalSpeed = 5;
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
}

void Mario::moveLeft(int prev)
{
    if(prev >= position.y + height)
    {
        distance -= horizontalSpeed;
    }
}

/*void Mario::jump()
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
}*/



