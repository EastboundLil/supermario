#ifndef ENEMY_H
#define ENEMY_H

#include "Terrain.h"
#include <cmath>

#define PI 3.14159265

class Enemy : public Terrain
{
public:
    Enemy(Position pos, std::string type, int value, int height, double distance, int horizontalSpeed) :
        Terrain(pos, type, height),
        value(value),
        distance(distance),
        horizontalSpeed(horizontalSpeed),
        acceleration(1),
        speed(0),
        movingLeft(true),
        health(1),
        thorned(false)
    {

    }

    virtual void move(int prev, int next)
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

    virtual ~Enemy() {};

    int     getDistance()   {return distance;}
    int     getSpeed()      {return speed;}
    bool    isMovingLeft()  {return movingLeft;}
    int     getHealth()     {return health;}
    bool    isThorned()     {return thorned;}
    int     getValue()      {return value;}

    void zeroSpeed()        {speed = 0;}
    void changeDirection()  {movingLeft = !movingLeft;}
    void decrementHealth()  {health--;}
    void incrementHealth()  {health++;}
    void setHealth(int h)   {health = h;}

protected:
    int     value;
    double  distance;
    int     horizontalSpeed;
    int     acceleration;
    int     speed;
    bool    movingLeft;
    int     health;
    bool    thorned;

};

#endif // ENEMY_H
