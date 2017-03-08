#ifndef MARIO_H
#define MARIO_H

#include "Position.h"
#include "Terrain.h"
#include "graphics.hpp"

class Mario : public Terrain
{
public:
    Mario();
    Mario(int x, int y);

    void moveRight(int height);
    void moveLeft(int height);
    void jump();
    void fall(int groundLevel);

    int getDistance() {return distance;}
    int getSpeed() {return speed;}

private:
    int distance = 300;
    int acceleration = 1;
    int speed = 0;
    int horizontalSpeed = 5;
};

#endif // MARIO_H
