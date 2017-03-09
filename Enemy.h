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
        speed(0),
        movingLeft(true)
    {

    }

    virtual void move(int prev, int next, int distance)
    {
        if(movingLeft) moveLeft(prev);
        else moveRight(next);
    }

    virtual void moveRight(int next)
    {
        if(next >= position.y + height)
        {
            distance += horizontalSpeed;
            position.x += horizontalSpeed;
        }
        else changeDirection();
    }

   virtual void moveLeft(int prev)
    {
        if(prev >= position.y + height)
        {
            distance -= horizontalSpeed;
            position.x -= horizontalSpeed;
        }
        else changeDirection();
    }

    virtual void jump()
    {
        //do nothing;
    }

    virtual void fall(int groundLevel)
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
    bool changeDirection() {movingLeft = !movingLeft;}
    bool getMovingLeft() {return movingLeft;}

    void zeroSpeed() {speed = 0;}

protected:
    int distance;
    int acceleration;
    int speed;
    int horizontalSpeed;
    bool movingLeft;
};

#endif // ENEMY_H
