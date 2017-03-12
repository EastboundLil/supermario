#ifndef GAME_H
#define GAME_H

#include "graphics.hpp"
#include "Logger.h"
#include "fstream"
#include <vector>
#include <list>
#include <map>
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
    void generateTerrain();
    void generateEnemies();

    void addGround();
    void addPipe();
    void addCliff();
    void addStair();
    void addDownStair();

    bool collided();
    bool fallen();

    void draw();
    void drawBackgound();
    void drawMario();
    void drawLevel();
    void drawEnemies();

    void drawMenu();
    void drawCursor();

    void drawTerrain(std::string type, int height, int offset);
    void drawEnemy(std::string type, int distance, int y, bool isMovingLeft, bool timer);

    void readTexture(std::string filename, canvas& texture);
    void readTexture(std::string filename,  canvas& left,
                                            canvas& right);
    void readTexture(std::string filename,  canvas& leftTexture,
                                            canvas& rightTexture,
                                            canvas& leftMoveTexture,
                                            canvas& rightMoveTexture);

    const int WINDOW_HEIGHT;
    const int WINDOW_WIDTH;

    std::vector<Terrain*> level;
    std::list<Enemy*> enemies;
    std::map<std::string, canvas> terrainTextureMap;
    std::map<std::string, std::vector<canvas> > enemyTextureMap;

    std::vector<std::string> tt;
    std::vector<std::string> et;

    int numberOfTerrainTypes;
    int numberOfEnemieTypes;

    event ev;
    Mario mario;

    canvas marioRightTexture;
    canvas marioLeftTexture;
    canvas marioJumpRightTexture;
    canvas marioJumpLeftTexture;
    canvas marioRunRightTexture;
    canvas marioRunLeftTexture;

    std::fstream f;

    bool movingRight = false;
    bool movingLeft = false;

    int cursor;
    bool quitGame;
    int difficulty;
    std::vector<std::string>* actualMenu;
    std::vector<std::string>  mainMenu;
    std::vector<std::string>  difficultyMenu;
    std::vector<std::string>  characterMenu;

    void exectuteMenuElement();

};
#endif // GAME_H
