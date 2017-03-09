#include "Game.h"

Game::Game() :
    WINDOW_HEIGHT(600),
    WINDOW_WIDTH(1000)
{
    gout.open(WINDOW_WIDTH,WINDOW_HEIGHT);
    tt = {  "background",
            "ground",
            "cliff",
            "pipe",
            "pipehelper",
            "end",
            "endhelper",
            "stair",
            "stair2",
            "stair3",
            "stair4",
            "stair5"};

    et = {  "goomba",
            "koopa",
            "redkoopa",
            "bluekoopa",
            "yellowkoopa",
            "blackkoopa",
            "spiny"};

    for(std::string s : tt)
        terrainTextureMap[s] = canvas();

    std::vector<canvas> c;
    c.push_back(canvas());
    c.push_back(canvas());
    c.push_back(canvas());
    c.push_back(canvas());

    for(std::string s : et)
    {
        enemyTextureMap[s] = c;
    }


    for(std::map<std::string,canvas>::iterator t = terrainTextureMap.begin(); t != terrainTextureMap.end(); t++)
        readTexture(t->first,t->second);
    for(std::map<std::string,std::vector<canvas> >::iterator e = enemyTextureMap.begin(); e != enemyTextureMap.end(); e++)
        readTexture(e->first,e->second.at(0),e->second.at(1),e->second.at(2),e->second.at(3));

    readTexture("mario",marioLeftTexture,marioRightTexture);
    readTexture("jump",marioJumpLeftTexture,marioJumpRightTexture);
    readTexture("run",marioRunLeftTexture,marioRunRightTexture);

}

bool Game::newGame()
{
    bool endLevel = false;
    mario.reset(WINDOW_WIDTH/2,0);
    generateLevel();
    gin.timer(1);
    movingRight = false;
    movingLeft = false;

    while(gin >> ev && ev.keycode != key_space) {

        if(endLevel)
        {
            mario.fall(WINDOW_HEIGHT+7000);
            if(mario.getHeight()+mario.getPosition().y == WINDOW_HEIGHT+7000) break;
        }
        else
        {
            if(ev.keycode == key_escape) return false;

            int CURRENT_HEIGHT  = WINDOW_HEIGHT - level.at((mario.getDistance()+25)/50)->getHeight();
            int PREV_HEIGHT     = WINDOW_HEIGHT - level.at((mario.getDistance()/50))->getHeight();
            int NEXT_HEIGHT     = WINDOW_HEIGHT - level.at((mario.getDistance()/50)+1)->getHeight();

            if(ev.keycode == key_right)     movingRight = true;
            if(ev.keycode == -key_right)    movingRight = false;
            if(ev.keycode == key_left)      movingLeft = true;
            if(ev.keycode == -key_left)     movingLeft = false;
            if(ev.keycode == key_up)        mario.jump();

            if(movingRight) mario.moveRight(NEXT_HEIGHT);
            if(movingLeft) mario.moveLeft(PREV_HEIGHT);
            mario.fall(CURRENT_HEIGHT);

            for(Enemy* it : enemies)
            {
                if(ev.keycode == key_up)
                    it->jump();
                it->move(WINDOW_HEIGHT - level.at(((it->getDistance())/50))->getHeight(),
                         WINDOW_HEIGHT - level.at(((it->getDistance())/50)+1)->getHeight(),
                         mario.getDistance());
                it->fall(WINDOW_HEIGHT - level.at((it->getDistance()+25)/50)->getHeight());
            }
            endLevel = collided() || fallen();
            if(endLevel)
            {
                mario.setSpeed(0);
                mario.jump();
            }
        }
        draw();
    }

    return true;
}

void Game::generateLevel()
{

    for(Terrain* it : level)
    {
        delete it;
    }
    level.clear();

    for(Enemy* it : enemies)
    {
        delete it;
    }
    enemies.clear();

    srand(time(NULL));

    level.push_back(new Ground());
    level.push_back(new End());
    level.push_back(new EndHelper());

    for(int i = 0; i < 20; ++i)
    {
        level.push_back(new Ground());
    }

    level.push_back(new Stair());
    level.push_back(new Stair2());
    level.push_back(new Stair3());
    level.push_back(new Stair4());
    level.push_back(new Stair5());

    for(int i = 0; i < 50; ++i)
    {
        if((i+1) % 10 == 0)
        {
            level.push_back(new Pipe());
            level.push_back(new PipeHelper());
        }
        else if((i+1) % 7 == 0)
        {
            level.push_back(new Cliff());
            level.push_back(new Cliff());
            level.push_back(new Cliff());
        }
        else level.push_back(new Ground());
    }

    level.push_back(new End());
    level.push_back(new Ground());

    for(int i=0; i < 10; i++)
    {
        int r = rand() % 7;
        int pos = (rand() % ((level.size()*50)-700)) + 700;
        switch(r){
            case 0: enemies.push_back(new Goomba(pos)); break;
            case 1: enemies.push_back(new Koopa(pos)); break;
            case 3: enemies.push_back(new RedKoopa(pos)); break;
            case 4: enemies.push_back(new BlueKoopa(pos)); break;
            case 5: enemies.push_back(new YellowKoopa(pos)); break;
            case 6: enemies.push_back(new BlackKoopa(pos)); break;
            case 7: enemies.push_back(new Spiny(pos)); break;
        }
    }

}

bool Game::collided()
{
    for(std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++)
    {
        if(mario.getDistance()+25 >= (*it)->getDistance()-25 &&
           mario.getDistance()-25 <= (*it)->getDistance()+25 &&
           mario.getPosition().y + mario.getHeight() == (*it)->getPosition().y + (*it)->getHeight())
        {
            return true;
        }
        else if(mario.getDistance()+25 >= (*it)->getDistance()-25 &&
           mario.getDistance()-25 <= (*it)->getDistance()+25 &&
           mario.getPosition().y + mario.getHeight() <= (*it)->getPosition().y+10 &&
           mario.getPosition().y + mario.getHeight() >= (*it)->getPosition().y-10 &&
           mario.getSpeed() > 0 )
        {
            if((*it)->isThorned()) return true;
            else
            {
                (*it)->decrementHealth();
                if((*it)->getHealth() == 0)
                {
                    delete (*it);
                    enemies.erase(it);
                }
                mario.zeroSpeed();
                mario.jump();
            }
        }

    }
}

bool Game::fallen()
{
    return (mario.getPosition().y > WINDOW_HEIGHT);
}

void Game::run()
{
    while(newGame())
    {
    }
}

void Game::draw()
{
    drawBackgound();
    drawLevel();
    drawMario();
    drawEnemies();

    gout << refresh;
}

void Game::drawBackgound()
{
    gout    << stamp(terrainTextureMap["background"],0,0);;
}

void Game::drawMario()
{
    if(mario.getSpeed() != 0 && movingRight)
        gout << stamp(marioJumpRightTexture,mario.getPosition().x,mario.getPosition().y);
    else if(mario.getSpeed() != 0 && movingLeft)
        gout << stamp(marioJumpLeftTexture,mario.getPosition().x,mario.getPosition().y);
    else if(movingLeft && (ev.time / 30) % 10 < 5)
        gout << stamp(marioRunLeftTexture,mario.getPosition().x,mario.getPosition().y);
    else if(movingLeft && (ev.time / 30) % 10 >= 5)
        gout << stamp(marioLeftTexture,mario.getPosition().x,mario.getPosition().y);
    else if(movingRight && (ev.time / 30) % 10 < 5)
        gout << stamp(marioRunRightTexture,mario.getPosition().x,mario.getPosition().y);
    else if(movingRight && (ev.time / 30) % 10 >= 5)
        gout << stamp(marioRightTexture,mario.getPosition().x,mario.getPosition().y);
    else if(mario.getSpeed() != 0 && !mario.isMovingLeft())
        gout << stamp(marioJumpRightTexture,mario.getPosition().x,mario.getPosition().y);
    else if(mario.getSpeed() != 0 && mario.isMovingLeft())
        gout << stamp(marioJumpLeftTexture,mario.getPosition().x,mario.getPosition().y);
    else if(mario.isMovingLeft())
        gout << stamp(marioLeftTexture,mario.getPosition().x,mario.getPosition().y);
    else if(!mario.isMovingLeft())
        gout << stamp(marioRightTexture,mario.getPosition().x,mario.getPosition().y);
}

void Game::drawLevel()
{
    int offset = 500;
    for(Terrain *it : level)
    {
        if(it->getType() != "pipehelper" &&
           it->getType() != "endhelper"  &&
           it->getType() != "cliff")
                drawTerrain(it->getType(),it->getHeight(),offset);
        offset += 50;
    }
}

void Game::drawTerrain(std::string type, int height, int offset)
{
    gout << stamp(terrainTextureMap[type], offset-mario.getDistance(),WINDOW_HEIGHT-height);
}

void Game::drawEnemies()
{
    for(Enemy* it : enemies)
    {
        drawEnemy(it->getType(), it->getDistance(), it->getPosition().y, it->isMovingLeft(), (ev.time / 30) % 10 < 5);
    }
}

void Game::drawEnemy(std::string type, int distance, int y, bool isMovingLeft, bool timer)
{
    if(!isMovingLeft && timer)
            gout << stamp(enemyTextureMap[type].at(0), 500 + distance - mario.getDistance(), y);
    else if(isMovingLeft && timer)
            gout << stamp(enemyTextureMap[type].at(1), 500 + distance - mario.getDistance(), y);
    else if(!isMovingLeft && !timer)
            gout << stamp(enemyTextureMap[type].at(2), 500 + distance - mario.getDistance(), y);
    else if(isMovingLeft && !timer)
            gout << stamp(enemyTextureMap[type].at(3), 500 + distance - mario.getDistance(), y);
}

void Game::readTexture(std::string filename, canvas& texture)
{
    filename = "pics/" + filename + ".kep";
    LOG("reading file: " << filename);
    f.open(filename);

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        texture.open(w,h);
        texture.transparent(true);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                texture << move_to(j,i);
                texture << color(r,g,b);
                texture << dot;
            }
        }
        LOG(filename << " read successfully");
    }
    else LOG("########## File " << filename << " could not be opened! ##########");

    f.close();
}

void Game::readTexture(std::string filename, canvas& leftTexture, canvas& rightTexture)
{
    filename = "pics/" + filename + ".kep";
    LOG("reading file: " << filename);
    f.open(filename);

    rightTexture.transparent(true);
    leftTexture.transparent(true);

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        rightTexture.open(w,h);
        leftTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                rightTexture << move_to(j,i);
                rightTexture << color(r,g,b);
                rightTexture << dot;

                leftTexture << move_to(w-j,i);
                leftTexture << color(r,g,b);
                leftTexture << dot;
            }
        }
        LOG(filename << " read successfully");
    }

    else LOG("########## File " << filename << " could not be opened! ##########");

    f.close();
}

void Game::readTexture(std::string filename, canvas& leftTexture, canvas& rightTexture, canvas& leftMoveTexture, canvas& rightMoveTexture)
{
    readTexture(filename, leftTexture, rightTexture);
    readTexture(filename + "move", leftMoveTexture, rightMoveTexture);
}
