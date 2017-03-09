#ifndef GAME_H
#define GAME_H

#include "graphics.hpp"
#include "Logger.h"
#include "fstream"
#include <vector>
#include <list>
#include <cstdlib>
#include <time.h>
#include "Mario.h"
#include "TextureTypes.h"
#include "EnemyTypes.h"

using namespace genv;

class Game
{
public:
    Game();
    void run();

private:
    bool newGame();
    void generateLevel();

    bool collided();
    bool fallen();

    void draw();
    void drawBackgound();
    void drawMario();
    void drawLevel();
    void drawEnemies();

    void readBackgroundTexture();
    void readGroundTexture();
    void readPipeTexture();
    void readMarioTexture();
    void readMarioJumpTexture();
    void readMarioRunTexture();
    void readGoombaTexture();
    void readKoopaTexture();
    void readKoopaMoveTexture();
    void readRedKoopaTexture();
    void readRedKoopaMoveTexture();
    void readBlueKoopaTexture();
    void readBlueKoopaMoveTexture();
    canvas readTexture(std::string filename);

    std::vector<Terrain*> getLevel();

    const int WINDOW_HEIGHT;
    const int WINDOW_WIDTH;

    std::vector<Terrain*> level;
    std::list<Enemy*> enemies;

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
    canvas goombaLeftTexture;
    canvas goombaRightTexture;
    canvas koopaLeftTexture;
    canvas koopaRightTexture;
    canvas koopaLeftMoveTexture;
    canvas koopaRightMoveTexture;
    canvas redKoopaLeftTexture;
    canvas redKoopaRightTexture;
    canvas redKoopaLeftMoveTexture;
    canvas redKoopaRightMoveTexture;
    canvas blueKoopaLeftTexture;
    canvas blueKoopaRightTexture;
    canvas blueKoopaLeftMoveTexture;
    canvas blueKoopaRightMoveTexture;


    std::fstream f;

    bool movingRight = false;
    bool movingLeft = false;
};

#endif // GAME_H
