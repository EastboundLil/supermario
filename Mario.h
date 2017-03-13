#ifndef MARIO_H
#define MARIO_H

#include "Position.h"
#include "Enemy.h"
#include "graphics.hpp"

class Mario : public Enemy
{
public:
    Mario();

    void reset(int x, int y);
    void init() {health = 2; score = 0;}

    void moveLeft(int prev);
    void moveRight(int next);
    void jump();
    void setSpeed(int s) {speed = s;}
    void sprintOn() {sprint = 2;}
    void sprintOff(){sprint = 0;}

    int getScore() {return score;}
    void addScore(int amount) {score += amount;}
    void halveScore() {score = score/2;}

    Position getPosition() {return position;}


private:
    int score;
    int sprint;
};

#endif // MARIO_H
