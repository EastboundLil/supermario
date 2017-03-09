#ifndef ENEMYTYPES_H
#define ENEMYTYPES_H

#include "Enemy.h"

class Goomba : public Enemy
{
public:
    Goomba(int distance) : Enemy(Position(800,100), "goomba", 46, distance, 1) {}
};

class Koopa : public Enemy
{
protected:
    Koopa(int distance, std::string type) : Enemy(Position(800,100), type, 76, distance, 1) {}
public:
    Koopa(int distance) : Enemy(Position(800,100), "koopa", 76, distance, 1) {}
};

class RedKoopa : public Koopa
{
protected:
    RedKoopa(int distance, std::string type) : Koopa(distance, type) {}
public:
    RedKoopa(int distance) : Koopa(distance, "redkoopa") {}

    void moveRight(int next)
    {
        if(next == position.y + height)
        {
            distance += horizontalSpeed;
            position.x += horizontalSpeed;
        }
        else changeDirection();
    }

    void moveLeft(int prev)
    {
        if(prev == position.y + height)
        {
            distance -= horizontalSpeed;
            position.x -= horizontalSpeed;
        }
        else changeDirection();
    }
};

class BlueKoopa : public RedKoopa
{
public:
    BlueKoopa(int distance) : RedKoopa(distance, "bluekoopa") { horizontalSpeed = 3; }
};

#endif // ENEMYTYPES_H
