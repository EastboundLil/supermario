#ifndef ENEMY_H
#define ENEMY_H

#include "Terrain.h"

class Enemy : public Terrain
{
public:
    Enemy(Position pos,std::string type, int height, int distance, int horizontalSpeed) :
        Terrain(pos, type, height),
        distance(distance),
        horizontalSpeed(horizontalSpeed),
        acceleration(1),
        speed(0)
    {

    }

    void moveRight(int next)
    {
        if(next >= position.y + height)
        {
            distance += horizontalSpeed;
            position.x += horizontalSpeed;
        }
    }

    void moveLeft(int prev)
    {
        if(prev >= position.y + height)
        {
            distance -= horizontalSpeed;
            position.x -= horizontalSpeed;
        }
    }

    void jump()
    {
        if(speed == 0) speed = -20;
        position.y--;
    }

    void fall(int groundLevel)
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

    int getDistance() {return distance;}
    int getSpeed() {return speed;}

protected:
    int distance;
    int acceleration;
    int speed;
    int horizontalSpeed;
};

#endif // ENEMY_H
