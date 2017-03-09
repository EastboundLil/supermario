#include "Game.h"

Game::Game() :
    WINDOW_HEIGHT(600),
    WINDOW_WIDTH(1000)
{
    gout.open(WINDOW_WIDTH,WINDOW_HEIGHT);

    readBackgroundTexture();
    readGroundTexture();
    readPipeTexture();
    readEndTexture();

    readMarioTexture();
    readMarioJumpTexture();
    readMarioRunTexture();

    readGoombaTexture();
    readKoopaTexture();
    readKoopaMoveTexture();
    readRedKoopaTexture();
    readRedKoopaMoveTexture();
    readBlueKoopaTexture();
    readBlueKoopaMoveTexture();
    readYellowKoopaTexture();
    readYellowKoopaMoveTexture();
    readBlackKoopaTexture();
    readBlackKoopaMoveTexture();
    readSpinyTexture();
    readSpinyMoveTexture();
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
    /*for(int i = 0; i < 50; ++i)
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
    }*/
    level.push_back(new End());
    level.push_back(new Ground());

    for(int i=0; i < 1; i++)
    {
        //enemies.push_back(new Goomba(750));
        //enemies.push_back(new Koopa(850));
        //enemies.push_back(new RedKoopa(950));
        //enemies.push_back(new BlueKoopa(1050));
        //enemies.push_back(new YellowKoopa(1000));
        //enemies.push_back(new BlackKoopa(720));
        enemies.push_back(new Spiny(750));
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
    gout    << stamp(backgroundTexture,0,0);
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
        if(it->getType() == "ground") gout << stamp(groundTexture, offset-mario.getDistance(),WINDOW_HEIGHT-it->getHeight());
        else if(it->getType() == "pipe") gout << stamp(pipeTexture, offset-mario.getDistance(),WINDOW_HEIGHT-it->getHeight());
        else if(it->getType() == "end") gout << stamp(endTexture, offset-mario.getDistance(),WINDOW_HEIGHT-it->getHeight());

        offset += 50;
    }
}

void Game::drawEnemies()
{
    for(Enemy* it : enemies)
    {
        //////////////////GOOMBA//////////////////
        if(it->getType() == "goomba" && (ev.time / 30) % 10 < 5)
            gout << stamp(goombaLeftTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "goomba" && (ev.time / 30) % 10 >= 5)
            gout << stamp(goombaRightTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);

        //////////////////KOOPA//////////////////
        else if(it->getType() == "koopa" && it->isMovingLeft() && (ev.time / 30) % 10 < 5)
            gout << stamp(koopaLeftTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "koopa" && it->isMovingLeft() && (ev.time / 30) % 10 >= 5)
            gout << stamp(koopaLeftMoveTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "koopa" && !it->isMovingLeft() && (ev.time / 30) % 10 < 5)
            gout << stamp(koopaRightTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "koopa" && !it->isMovingLeft() && (ev.time / 30) % 10 >= 5)
            gout << stamp(koopaRightMoveTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);

        //////////////////RED KOOPA//////////////////
        else if(it->getType() == "redkoopa" && it->isMovingLeft() && (ev.time / 30) % 10 < 5)
            gout << stamp(redKoopaLeftTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "redkoopa" && it->isMovingLeft() && (ev.time / 30) % 10 >= 5)
            gout << stamp(redKoopaLeftMoveTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "redkoopa" && !it->isMovingLeft() && (ev.time / 30) % 10 < 5)
            gout << stamp(redKoopaRightTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "redkoopa" && !it->isMovingLeft() && (ev.time / 30) % 10 >= 5)
            gout << stamp(redKoopaRightMoveTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);

        //////////////////BLUE KOOPA//////////////////
        else if(it->getType() == "bluekoopa" && it->isMovingLeft() && (ev.time / 30) % 10 < 5)
            gout << stamp(blueKoopaLeftTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "bluekoopa" && it->isMovingLeft() && (ev.time / 30) % 10 >= 5)
            gout << stamp(blueKoopaLeftMoveTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "bluekoopa" && !it->isMovingLeft() && (ev.time / 30) % 10 < 5)
            gout << stamp(blueKoopaRightTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "bluekoopa" && !it->isMovingLeft() && (ev.time / 30) % 10 >= 5)
            gout << stamp(blueKoopaRightMoveTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);

        //////////////////YELLOW KOOPA//////////////////
        else if(it->getType() == "yellowkoopa" && it->isMovingLeft() && (ev.time / 30) % 10 < 5)
            gout << stamp(yellowKoopaLeftTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "yellowkoopa" && it->isMovingLeft() && (ev.time / 30) % 10 >= 5)
            gout << stamp(yellowKoopaLeftMoveTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "yellowkoopa" && !it->isMovingLeft() && (ev.time / 30) % 10 < 5)
            gout << stamp(yellowKoopaRightTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "yellowkoopa" && !it->isMovingLeft() && (ev.time / 30) % 10 >= 5)
            gout << stamp(yellowKoopaRightMoveTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);

        //////////////////BLACK KOOPA//////////////////
        else if(it->getType() == "blackkoopa" && it->isMovingLeft() && (ev.time / 30) % 10 < 5)
            gout << stamp(blackKoopaLeftTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "blackkoopa" && it->isMovingLeft() && (ev.time / 30) % 10 >= 5)
            gout << stamp(blackKoopaLeftMoveTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "blackkoopa" && !it->isMovingLeft() && (ev.time / 30) % 10 < 5)
            gout << stamp(blackKoopaRightTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "blackkoopa" && !it->isMovingLeft() && (ev.time / 30) % 10 >= 5)
            gout << stamp(blackKoopaRightMoveTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);

        //////////////////SPINY//////////////////
        else if(it->getType() == "spiny" && it->isMovingLeft() && (ev.time / 30) % 10 < 5)
            gout << stamp(spinyLeftTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "spiny" && it->isMovingLeft() && (ev.time / 30) % 10 >= 5)
            gout << stamp(spinyLeftMoveTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "spiny" && !it->isMovingLeft() && (ev.time / 30) % 10 < 5)
            gout << stamp(spinyRightTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "spiny" && !it->isMovingLeft() && (ev.time / 30) % 10 >= 5)
            gout << stamp(spinyRightMoveTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
    }
}

canvas Game::readTexture(std::string filename)
{
    f.open(filename);
    canvas C;

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        C.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                C << move_to(j,i);
                C << color(r,g,b);
                C << dot;
            }
        }
    }
    else LOG("########## File could not be opened! ##########");

    f.close();
    return C;
}

void Game::readBackgroundTexture()
{
    f.open("pics/background.kep");
    //canvas C;

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        backgroundTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                backgroundTexture << move_to(j,i);
                backgroundTexture << color(r,g,b);
                backgroundTexture << dot;
            }
        }
    }
    else LOG("########## File could not be opened! ##########");

    f.close();
    //backgroundTexture = C;
}

void Game::readGroundTexture()
{
    f.open("pics/ground.kep");
    //canvas C;

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        groundTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                groundTexture << move_to(j,i);
                groundTexture << color(r,g,b);
                groundTexture << dot;
            }
        }
    }
    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}

void Game::readPipeTexture()
{
    f.open("pics/pipe.kep");
    //canvas C;

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        pipeTexture.open(w,h);
        pipeTexture.transparent(true);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                pipeTexture << move_to(j,i);
                pipeTexture << color(r,g,b);
                pipeTexture << dot;
            }
        }
    }
    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}

void Game::readEndTexture()
{
    f.open("pics/end.kep");
    //canvas C;

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        endTexture.open(w,h);
        endTexture.transparent(true);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                endTexture << move_to(j,i);
                endTexture << color(r,g,b);
                endTexture << dot;
            }
        }
    }
    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}

void Game::readMarioTexture()
{
    f.open("pics/mario.kep");
    //canvas C;

    marioRightTexture.transparent(true);
    marioLeftTexture.transparent(true);

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        marioRightTexture.open(w,h);
        marioLeftTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                marioRightTexture << move_to(j,i);
                marioRightTexture << color(r,g,b);
                marioRightTexture << dot;

                marioLeftTexture << move_to(w-j,i);
                marioLeftTexture << color(r,g,b);
                marioLeftTexture << dot;
            }
        }
    }

    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}

void Game::readMarioJumpTexture()
{
    f.open("pics/jump.kep");
    //canvas C;

    marioJumpRightTexture.transparent(true);
    marioJumpLeftTexture.transparent(true);

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        marioJumpRightTexture.open(w,h);
        marioJumpLeftTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                marioJumpRightTexture << move_to(j,i);
                marioJumpRightTexture << color(r,g,b);
                marioJumpRightTexture << dot;

                marioJumpLeftTexture << move_to(w-j,i);
                marioJumpLeftTexture << color(r,g,b);
                marioJumpLeftTexture << dot;
            }
        }
    }

    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}

void Game::readMarioRunTexture()
{
    f.open("pics/run.kep");
    //canvas C;

    marioRunRightTexture.transparent(true);
    marioRunLeftTexture.transparent(true);

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        marioRunRightTexture.open(w,h);
        marioRunLeftTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                marioRunRightTexture << move_to(j,i);
                marioRunRightTexture << color(r,g,b);
                marioRunRightTexture << dot;

                marioRunLeftTexture << move_to(w-j,i);
                marioRunLeftTexture << color(r,g,b);
                marioRunLeftTexture << dot;
            }
        }
    }

    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}

void Game::readGoombaTexture()
{
    f.open("pics/goomba.kep");
    //canvas C;

    goombaLeftTexture.transparent(true);
    goombaRightTexture.transparent(true);

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        goombaLeftTexture.open(w,h);
        goombaRightTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                goombaLeftTexture << move_to(j,i);
                goombaLeftTexture << color(r,g,b);
                goombaLeftTexture << dot;

                goombaRightTexture << move_to(w-j,i);
                goombaRightTexture << color(r,g,b);
                goombaRightTexture << dot;
            }
        }
    }

    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}

void Game::readKoopaTexture()
{
    f.open("pics/koopaStand.kep");
    //canvas C;

    koopaLeftTexture.transparent(true);
    koopaRightTexture.transparent(true);

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        koopaLeftTexture.open(w,h);
        koopaRightTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                koopaLeftTexture << move_to(j,i);
                koopaLeftTexture << color(r,g,b);
                koopaLeftTexture << dot;

                koopaRightTexture << move_to(w-j,i);
                koopaRightTexture << color(r,g,b);
                koopaRightTexture << dot;
            }
        }
    }

    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}

void Game::readKoopaMoveTexture()
{
    f.open("pics/koopaMove.kep");
    //canvas C;

    koopaLeftMoveTexture.transparent(true);
    koopaRightMoveTexture.transparent(true);

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        koopaLeftMoveTexture.open(w,h);
        koopaRightMoveTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                koopaLeftMoveTexture << move_to(j,i);
                koopaLeftMoveTexture << color(r,g,b);
                koopaLeftMoveTexture << dot;

                koopaRightMoveTexture << move_to(w-j,i);
                koopaRightMoveTexture << color(r,g,b);
                koopaRightMoveTexture << dot;
            }
        }
    }

    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}

void Game::readRedKoopaTexture()
{
    f.open("pics/redKoopaStand.kep");
    //canvas C;

    redKoopaLeftTexture.transparent(true);
    redKoopaRightTexture.transparent(true);

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        redKoopaLeftTexture.open(w,h);
        redKoopaRightTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                redKoopaLeftTexture << move_to(j,i);
                redKoopaLeftTexture << color(r,g,b);
                redKoopaLeftTexture << dot;

                redKoopaRightTexture << move_to(w-j,i);
                redKoopaRightTexture << color(r,g,b);
                redKoopaRightTexture << dot;
            }
        }
    }

    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}

void Game::readRedKoopaMoveTexture()
{
    f.open("pics/redKoopaMove.kep");
    //canvas C;

    redKoopaLeftMoveTexture.transparent(true);
    redKoopaRightMoveTexture.transparent(true);

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        redKoopaLeftMoveTexture.open(w,h);
        redKoopaRightMoveTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                redKoopaLeftMoveTexture << move_to(j,i);
                redKoopaLeftMoveTexture << color(r,g,b);
                redKoopaLeftMoveTexture << dot;

                redKoopaRightMoveTexture << move_to(w-j,i);
                redKoopaRightMoveTexture << color(r,g,b);
                redKoopaRightMoveTexture << dot;
            }
        }
    }

    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}

void Game::readBlueKoopaTexture()
{
    f.open("pics/blueKoopaStand.kep");
    //canvas C;

    blueKoopaLeftTexture.transparent(true);
    blueKoopaRightTexture.transparent(true);

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        blueKoopaLeftTexture.open(w,h);
        blueKoopaRightTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                blueKoopaLeftTexture << move_to(j,i);
                blueKoopaLeftTexture << color(r,g,b);
                blueKoopaLeftTexture << dot;

                blueKoopaRightTexture << move_to(w-j,i);
                blueKoopaRightTexture << color(r,g,b);
                blueKoopaRightTexture << dot;
            }
        }
    }

    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}

void Game::readBlueKoopaMoveTexture()
{
    f.open("pics/blueKoopaMove.kep");
    //canvas C;

    blueKoopaLeftMoveTexture.transparent(true);
    blueKoopaRightMoveTexture.transparent(true);

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        blueKoopaLeftMoveTexture.open(w,h);
        blueKoopaRightMoveTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                blueKoopaLeftMoveTexture << move_to(j,i);
                blueKoopaLeftMoveTexture << color(r,g,b);
                blueKoopaLeftMoveTexture << dot;

                blueKoopaRightMoveTexture << move_to(w-j,i);
                blueKoopaRightMoveTexture << color(r,g,b);
                blueKoopaRightMoveTexture << dot;
            }
        }
    }

    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}

void Game::readYellowKoopaTexture()
{
    f.open("pics/yellowKoopaStand.kep");
    //canvas C;

    yellowKoopaLeftTexture.transparent(true);
    yellowKoopaRightTexture.transparent(true);

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        yellowKoopaLeftTexture.open(w,h);
        yellowKoopaRightTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                yellowKoopaLeftTexture << move_to(j,i);
                yellowKoopaLeftTexture << color(r,g,b);
                yellowKoopaLeftTexture << dot;

                yellowKoopaRightTexture << move_to(w-j,i);
                yellowKoopaRightTexture << color(r,g,b);
                yellowKoopaRightTexture << dot;
            }
        }
    }

    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}

void Game::readYellowKoopaMoveTexture()
{
    f.open("pics/yellowKoopaMove.kep");
    //canvas C;

    yellowKoopaLeftMoveTexture.transparent(true);
    yellowKoopaRightMoveTexture.transparent(true);

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        yellowKoopaLeftMoveTexture.open(w,h);
        yellowKoopaRightMoveTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                yellowKoopaLeftMoveTexture << move_to(j,i);
                yellowKoopaLeftMoveTexture << color(r,g,b);
                yellowKoopaLeftMoveTexture << dot;

                yellowKoopaRightMoveTexture << move_to(w-j,i);
                yellowKoopaRightMoveTexture << color(r,g,b);
                yellowKoopaRightMoveTexture << dot;
            }
        }
    }

    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}

void Game::readBlackKoopaTexture()
{
    f.open("pics/blackKoopaStand.kep");
    //canvas C;

    blackKoopaLeftTexture.transparent(true);
    blackKoopaRightTexture.transparent(true);

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        blackKoopaLeftTexture.open(w,h);
        blackKoopaRightTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                blackKoopaLeftTexture << move_to(j,i);
                blackKoopaLeftTexture << color(r,g,b);
                blackKoopaLeftTexture << dot;

                blackKoopaRightTexture << move_to(w-j,i);
                blackKoopaRightTexture << color(r,g,b);
                blackKoopaRightTexture << dot;
            }
        }
    }

    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}

void Game::readBlackKoopaMoveTexture()
{
    f.open("pics/blackKoopaMove.kep");
    //canvas C;

    blackKoopaLeftMoveTexture.transparent(true);
    blackKoopaRightMoveTexture.transparent(true);

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        blackKoopaLeftMoveTexture.open(w,h);
        blackKoopaRightMoveTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                blackKoopaLeftMoveTexture << move_to(j,i);
                blackKoopaLeftMoveTexture << color(r,g,b);
                blackKoopaLeftMoveTexture << dot;

                blackKoopaRightMoveTexture << move_to(w-j,i);
                blackKoopaRightMoveTexture << color(r,g,b);
                blackKoopaRightMoveTexture << dot;
            }
        }
    }

    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}

void Game::readSpinyTexture()
{
    f.open("pics/spiny.kep");
    //canvas C;

    spinyLeftTexture.transparent(true);
    spinyRightTexture.transparent(true);

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        spinyLeftTexture.open(w,h);
        spinyRightTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                spinyLeftTexture << move_to(j,i);
                spinyLeftTexture << color(r,g,b);
                spinyLeftTexture << dot;

                spinyRightTexture << move_to(w-j,i);
                spinyRightTexture << color(r,g,b);
                spinyRightTexture << dot;
            }
        }
    }

    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}

void Game::readSpinyMoveTexture()
{
    f.open("pics/spinyMove.kep");
    //canvas C;

    spinyLeftMoveTexture.transparent(true);
    spinyRightMoveTexture.transparent(true);

    if(f.is_open())
    {
        int w,h,r,g,b = 0;
        f >> w;
        f >> h;

        spinyLeftMoveTexture.open(w,h);
        spinyRightMoveTexture.open(w,h);

        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                f >> r >> g >> b;
                spinyLeftMoveTexture << move_to(j,i);
                spinyLeftMoveTexture << color(r,g,b);
                spinyLeftMoveTexture << dot;

                spinyRightMoveTexture << move_to(w-j,i);
                spinyRightMoveTexture << color(r,g,b);
                spinyRightMoveTexture << dot;
            }
        }
    }

    else LOG("########## File could not be opened! ##########");

    f.close();
    //groundTexture = C;
}
