#ifndef GAME_H
#define GAME_H

#include "graphics.hpp"
#include "Logger.h"
#include "Window.h"
#include "fstream"

using namespace genv;

class Game
{
public:
    Game();
    void run();

private:
    void generateLevel();
    void draw();
    void drawBackgound();
    void drawMario();
    void readBackgroundTexture();
    void readGroundTexture();

    std::list<Terrain*> getLevel();

    const int WINDOW_HEIGHT;
    const int WINDOW_WIDTH;

    std::list<Terrain*> level;
    event ev;
    Window window;
    Mario mario;
    canvas backgroundTexture;
    canvas groundTexture;
    canvas marioTexture;

    std::fstream f;
};

#endif // GAME_H
