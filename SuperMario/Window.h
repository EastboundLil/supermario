#ifndef WINDOW_H
#define WINDOW_H

#include <list>

#include "Mario.h"
#include "Ground.h"

class Window
{
public:
    void generateLevel();
    std::list<Terrain*> getLevel();

private:

    //Mario mario;
    std::list<Terrain*> level;
};

#endif // WINDOW_H
