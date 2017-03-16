#ifndef MARIO_H
#define MARIO_H

#include "Logger.h"
#include "Position.h"
#include "Enemy.h"
#include "graphics.hpp"

class Mario : public Enemy
{
public:
    static Mario& getInstance();
    Mario(Mario const&) = delete;
    void operator=(Mario const&) = delete;

    void reset(int x, int y);
    void init() {life = 2; score = 0; health = 1;}

    void moveLeft(int prev);
    void moveRight(int next);
    void jump();
    void setSpeed(int s) {speed = s;}
    void sprintOn() {sprint = 2;}
    void sprintOff(){sprint = 0;}

    int getScore() {return score;}
    void addScore(int amount) {score += amount;}
    void halveScore() {score = score/2;}

    void incrementLife() {life++;}
    void decrementLife() {life--;}
    int getLife()        {return life;}

    bool isInvulnerable() {return invulnerable;}
    void triggerInvulnerability() {if(!invulnerable) invulnerable = true;}
    void tickInvulnerability();

    Position getPosition() {return position;}


private:
    Mario();

    int score;
    int sprint;
    int life;
    int invTimer;
    bool invulnerable;
};

#endif // MARIO_H
