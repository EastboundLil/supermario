#ifndef ENEMYTYPES_H
#define ENEMYTYPES_H

#include "Enemy.h"

struct EnemyTexture
{
    EnemyTexture(std::string type) : type(type) {}
    std::string type;
    canvas left;
    canvas right;
    canvas leftMove;
    canvas rightMove;
};

class Goomba : public Enemy
{
public:
    Goomba(int distance) : Enemy(Position(800,100), "goomba", 46, distance, 1) {}
};

class Koopa : public Enemy
{
protected:
    Koopa(int distance, std::string type) : Enemy(Position(800,100), type, 76, distance, 1) { health = 2; }
public:
    Koopa(int distance) : Enemy(Position(800,100), "koopa", 76, distance, 1) { health = 2; }
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

class YellowKoopa : public RedKoopa
{
protected:
    YellowKoopa(int distance, std::string type) : RedKoopa(distance, type) {}
public:
    YellowKoopa(int distance) : RedKoopa(distance, "yellowkoopa") { horizontalSpeed = 3; }

    void move(int prev, int next, int marioDist)
    {
        if(marioDist < distance) moveLeft(prev);
        else moveRight(next);
    }

    void moveRight(int next)
    {
        if(next == position.y + height)
        {
            distance += horizontalSpeed;
            position.x += horizontalSpeed;
            movingLeft = false;
        }
    }

    void moveLeft(int prev)
    {
        if(prev == position.y + height)
        {
            distance -= horizontalSpeed;
            position.x -= horizontalSpeed;
            movingLeft = true;
        }
    }
};

class BlackKoopa : public YellowKoopa
{
public:
    BlackKoopa(int distance) : YellowKoopa(distance, "blackkoopa") { horizontalSpeed = 3;}

    void jump()
    {
        if(speed == 0) speed = -25;
            position.y--;
    }
};

class Spiny : public RedKoopa
{
public:
    Spiny(int distance) : RedKoopa(distance,"spiny") { height = 54; thorned = true;}
};
#endif // ENEMYTYPES_H
