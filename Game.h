#ifndef GAME_H
#define GAME_H

#include "graphics.hpp"
#include "Logger.h"
#include "fstream"
#include <vector>
#include "Mario.h"
#include "TextureTypes.h"

using namespace genv;

class Game
{
public:
    Game();
    void run();

private:
    bool newGame();
    void generateLevel();
    void draw();
    void drawBackgound();
    void drawMario();
    void readBackgroundTexture();
    void readGroundTexture();
    void readPipeTexture();
    void readMarioTexture();
    void readMarioJumpTexture();
    void readMarioRunTexture();
    canvas readTexture(std::string filename);

    std::vector<Terrain*> getLevel();

    const int WINDOW_HEIGHT;
    const int WINDOW_WIDTH;

    std::vector<Terrain*> level;
    event ev;
    Mario mario;
    canvas backgroundTexture;
    canvas groundTexture;
    canvas pipeTexture;
    canvas marioRightTexture;
    canvas marioLeftTexture;
    canvas marioJumpRightTexture;
    canvas marioJumpLeftTexture;
    canvas marioRunRightTexture;
    canvas marioRunLeftTexture;

    std::fstream f;

    bool movingRight = false;
    bool movingLeft = false;
};

#endif // GAME_H
