#include "Window.h"

#include <cstdlib>
#include <time.h>
#include "Logger.h"

void Window::generateLevel()
{
    //srand(time(NULL));

    for(int i = 0; i < 20; ++i)
    {
        level.push_back(new Ground());
        LOG("Terrain " << i+1 << " created");
    }
    LOG("level size: " << level.size());
}

std::list<Terrain*> Window::getLevel()
{
    return level;
}
