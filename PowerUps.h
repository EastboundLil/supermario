#ifndef POWERUPS_H
#define POWERUPS_H

#include "EnemyTypes.h"

class PowerUp : public Enemy
{
public:
    PowerUp(std::string type, int distance, Position pos) :  Enemy(pos, type, 0, 50, distance, 1) {}
};

class oneUp : public PowerUp
{
public:
    oneUp(int distance, Position pos) : PowerUp("1up",distance,pos) {}
};

#endif // POWERUPS_H
