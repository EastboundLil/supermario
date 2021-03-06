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
#include <string>
#include <sstream>
#include "Mario.h"
#include "TextureTypes.h"
#include "EnemyTypes.h"
#include "PowerUps.h"
#include "MusicBox.h"

using namespace genv;

class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    bool newGame();
    void generateLevel();
    void generateTerrain();
    void generateEnemies();

    void selectWorld();

    void addGround();
    void addPipe();
    void addSmallPipe();
    void addHighPipe();
    void addCliff();
    void addHill();
    void addMediumHill();
    void addHighHill();
    void addStair();
    void addDownStair();

    std::vector<int> posOfPipes();

    bool collided();
    bool fallen();

    void draw();
    void drawBackgound();
    void drawMario();
    void drawHud();
    void drawLevel();
    void drawEnemies();
    void drawPowerUps();

    void drawMenu();
    void drawCursor();
    void drawGameOver();

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
    std::list<PowerUp*> powerUps;

    std::map<std::string, canvas> menuTextureMap;
    std::map<std::string, canvas>* terrainTextureMap;
    std::map<std::string, canvas> overworldTextureMap;
    std::map<std::string, canvas> undergroundTextureMap;
    std::map<std::string, std::vector<canvas> > enemyTextureMap;
    std::map<std::string, std::vector<canvas> > characterTextureMap;
    std::map<std::string, canvas> powerUpTextureMap;

    std::vector<std::string> mt;
    std::vector<std::string> tt;
    std::vector<std::string> wt;
    std::vector<std::string> et;
    std::vector<std::string> ct;
    std::vector<std::string> pt;

    int numberOfMenuTypes;
    int numberOfTerrainTypes;
    int numberOfEnemieTypes;
    int numberOfCharacterTypes;

    event ev;

    std::fstream f;
    MusicBox musicbox;

    bool movingRight = false;
    bool movingLeft = false;

    unsigned int cursor;
    bool quitGame;
    int castleDistance;
    int difficulty;
    std::string character;
    std::vector<std::string>* actualMenu;
    std::vector<std::string>  mainMenu;
    std::vector<std::string>  difficultyMenu;
    std::vector<std::string>  characterMenu;

    void executeMenuElement();

};
#endif // GAME_H
