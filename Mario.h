#ifndef MARIO_H
#define MARIO_H

#include "Position.h"
#include "Enemy.h"
#include "graphics.hpp"

class Mario : public Enemy
{
public:
    Mario();
    Mario(int x, int y);

    void reset(int x, int y);

    void moveLeft(int prev);
    void moveRight(int next);
    void jump();
    void setSpeed(int s) {speed = s;}
};

#endif // MARIO_H
