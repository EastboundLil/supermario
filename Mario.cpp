#include "Mario.h"

Mario& Mario::getInstance()
{
    static Mario instance;
    return instance;
}

Mario::Mario() :
    Enemy(Position(100,116), "mario", 0, 93, 300, 5),
    score(0)
{
    movingLeft = false;
    health = 1;
    sprint = 0;
    life = 3;
}

void Mario::tickInvulnerability()
{
    if(invulnerable)
    {
        invTimer++;
        if(invTimer == 200)
        {
            invulnerable = false;
            invTimer = 0;
        }
    }
}

void Mario::reset(int x, int y)
{
    setPosition(x,y);
    distance = 300;
    sprint = 0;
    invTimer = 0;
    invulnerable = false;
    health = 1;
}

void Mario::moveRight(int next)
{
    if(next >= position.y + height)
    {
        distance += horizontalSpeed + sprint;
    }
    movingLeft = false;
}

void Mario::moveLeft(int prev)
{
    if(prev >= position.y + height)
    {
        distance -= horizontalSpeed + sprint;
    }
    movingLeft = true;
}

void Mario::jump()
{
        if(speed == 0) speed = -20;
        position.y--;
}

