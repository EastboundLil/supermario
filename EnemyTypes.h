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
    Goomba(int distance) : Enemy(Position(800,100), "goomba", 50, 46, distance, 1) {}
};

class Koopa : public Enemy
{
protected:
    Koopa(int distance, std::string type, int value) : Enemy(Position(800,100), type, value, 76, distance, 1) { health = 2; }
public:
    Koopa(int distance) : Enemy(Position(800,100), "koopa", 100, 76, distance, 1) { health = 2; }
};

class RedKoopa : public Koopa
{
protected:
    RedKoopa(int distance, std::string type, int value) : Koopa(distance, type, value) {}
public:
    RedKoopa(int distance) : Koopa(distance, "redkoopa", 150) {}

    void moveRight(int next)
    {
        if(next == position.y + height ||
           next-50 == position.y + height)
        {
            distance += horizontalSpeed;
            position.x += horizontalSpeed;
        }
        else changeDirection();
    }

    void moveLeft(int prev)
    {
        if(prev == position.y + height ||
           prev-50 == position.y + height)
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
    BlueKoopa(int distance) : RedKoopa(distance, "bluekoopa", 200) { horizontalSpeed = 3; }
};

class YellowKoopa : public RedKoopa
{
protected:
    YellowKoopa(int distance, std::string type, int value) : RedKoopa(distance, type, value) {}
public:
    YellowKoopa(int distance) : RedKoopa(distance, "yellowkoopa", 250) { horizontalSpeed = 3; }

    void move(int prev, int next)
    {
        if(Mario::getInstance().getDistance() < distance) moveLeft(prev);
        else moveRight(next);
    }

    void moveRight(int next)
    {
        if(next == position.y + height ||
           next-50 == position.y + height)
        {
            distance += horizontalSpeed;
            position.x += horizontalSpeed;
            movingLeft = false;
        }
    }

    void moveLeft(int prev)
    {
        if(prev == position.y + height ||
           prev-50 == position.y + height)
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
    BlackKoopa(int distance) : YellowKoopa(distance, "blackkoopa", 300) { horizontalSpeed = 3;}

    void jump()
    {
        if(speed == 0) speed = -25;
            position.y--;
    }
};

class Spiny : public RedKoopa
{
public:
    Spiny(int distance) : RedKoopa(distance,"spiny",500) { height = 54; thorned = true;}
};

class Boo : public YellowKoopa
{
public:
    Boo(int distance) : YellowKoopa(distance,"boo",0) { height = 50; thorned = true;}

    void move(int prev, int next)
    {
        if(Mario::getInstance().getDistance() < distance) moveLeft();
        else moveRight();
    }

    void moveRight()
    {
        if(!(Mario::getInstance().isMovingLeft()))
        {
            double d = sqrt(pow(distance - Mario::getInstance().getDistance(),2) +
                pow(position.y - Mario::getInstance().getPosition().y+30,2));
            double x = Mario::getInstance().getDistance() - distance;
            double y = Mario::getInstance().getPosition().y+30 - position.y;
            distance += x/d;
            position.y += y/d;
            movingLeft = false;
        }
    }

    void moveLeft()
    {
        if(Mario::getInstance().isMovingLeft())
        {
            double d = sqrt(pow(distance - Mario::getInstance().getDistance(),2) +
                pow(position.y - Mario::getInstance().getPosition().y+30,2));
            double x = Mario::getInstance().getDistance() - distance;
            double y = Mario::getInstance().getPosition().y+30 - position.y;
            distance += x/d;
            position.y += y/d;
            movingLeft = true;
        }
    }

    void fall(int groundLevel)
    {
        //do nothing
    }
};

class PiranhaPlant : public Enemy
{
public:
    PiranhaPlant(int distance, int height) : Enemy(Position(800,(2*height)+10), "piranhaplant", 0, 100, distance, 0),
                                             tick(0) {speed = 1;}

    void move(int prev, int next)
    {
        if(sin(tick*PI/frequency) > 0.75)
        {
            tick++;
        }
        else if(sin(tick*PI/frequency) < 0.75 && sin(tick*PI/frequency) > -0.75 )
        {
            position.y += speed;
            tick++;
        }
        else if(sin(tick*PI/frequency) < -0.75)
        {
            tick++;
        }
        if(sin(tick*PI/frequency) > 0.75)
        {
            speed = 1;
        }
        else if(sin(tick*PI/frequency) < -0.75)
        {
            speed = -1;
        }
    }

    void fall(int groundLevel)
    {
        //do nothing
    }
private:
    int tick;
    int frequency = 300;
    int ground;
};

#endif // ENEMYTYPES_H
