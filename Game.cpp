#include "Game.h"

Game::Game() :
    WINDOW_HEIGHT(600),
    WINDOW_WIDTH(1000)
{
    gout.open(WINDOW_WIDTH,WINDOW_HEIGHT);

    readBackgroundTexture();
    readGroundTexture();
    readPipeTexture();
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
}

bool Game::newGame()
{
    bool endLevel = false;
    mario.reset(WINDOW_WIDTH/2,0);
    generateLevel();
    gin.timer(1);

    while(gin >> ev && ev.keycode != key_space && !endLevel) {

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
            it->move(WINDOW_HEIGHT - level.at(((it->getDistance())/50))->getHeight(),
                     WINDOW_HEIGHT - level.at(((it->getDistance())/50)+1)->getHeight());
            it->fall(WINDOW_HEIGHT - level.at((it->getDistance()+25)/50)->getHeight());
        }

        draw();

        endLevel = collided() || fallen();
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
    for(int i = 0; i < 20; ++i)
    {
        level.push_back(new Ground());
    }
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

    for(int i=0; i < 1; i++)
    {
        enemies.push_back(new Goomba(750+(i*50)));
        enemies.push_back(new Koopa(850+(i*50)));
        enemies.push_back(new RedKoopa(950+(i*50)));
        enemies.push_back(new BlueKoopa(1050+(i*50)));
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
            delete (*it);
            enemies.erase(it);
            mario.zeroSpeed();
            mario.jump();
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
    drawMario();
    drawLevel();
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
    else if(mario.getSpeed() != 0 && !mario.getMovingLeft())
        gout << stamp(marioJumpRightTexture,mario.getPosition().x,mario.getPosition().y);
    else if(mario.getSpeed() != 0 && mario.getMovingLeft())
        gout << stamp(marioJumpLeftTexture,mario.getPosition().x,mario.getPosition().y);
    else if(mario.getMovingLeft())
        gout << stamp(marioLeftTexture,mario.getPosition().x,mario.getPosition().y);
    else if(!mario.getMovingLeft())
        gout << stamp(marioRightTexture,mario.getPosition().x,mario.getPosition().y);
}

void Game::drawLevel()
{
    int offset = 500;
    for(Terrain *it : level)
    {
        if(it->getType() == "ground") gout << stamp(groundTexture, offset-mario.getDistance(),WINDOW_HEIGHT-it->getHeight());
        else if(it->getType() == "pipe") gout << stamp(pipeTexture, offset-mario.getDistance(),WINDOW_HEIGHT-it->getHeight());
        else if(it->getType() == "end") gout << stamp(groundTexture, offset-mario.getDistance(),WINDOW_HEIGHT-it->getHeight());

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
        else if(it->getType() == "koopa" && it->getMovingLeft() && (ev.time / 30) % 10 < 5)
            gout << stamp(koopaLeftTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "koopa" && it->getMovingLeft() && (ev.time / 30) % 10 >= 5)
            gout << stamp(koopaLeftMoveTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "koopa" && !it->getMovingLeft() && (ev.time / 30) % 10 < 5)
            gout << stamp(koopaRightTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "koopa" && !it->getMovingLeft() && (ev.time / 30) % 10 >= 5)
            gout << stamp(koopaRightMoveTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);

        //////////////////RED KOOPA//////////////////
        else if(it->getType() == "redkoopa" && it->getMovingLeft() && (ev.time / 30) % 10 < 5)
            gout << stamp(redKoopaLeftTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "redkoopa" && it->getMovingLeft() && (ev.time / 30) % 10 >= 5)
            gout << stamp(redKoopaLeftMoveTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "redkoopa" && !it->getMovingLeft() && (ev.time / 30) % 10 < 5)
            gout << stamp(redKoopaRightTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "redkoopa" && !it->getMovingLeft() && (ev.time / 30) % 10 >= 5)
            gout << stamp(redKoopaRightMoveTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);

        //////////////////BLUE KOOPA//////////////////
        else if(it->getType() == "bluekoopa" && it->getMovingLeft() && (ev.time / 30) % 10 < 5)
            gout << stamp(blueKoopaLeftTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "bluekoopa" && it->getMovingLeft() && (ev.time / 30) % 10 >= 5)
            gout << stamp(blueKoopaLeftMoveTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "bluekoopa" && !it->getMovingLeft() && (ev.time / 30) % 10 < 5)
            gout << stamp(blueKoopaRightTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
        else if(it->getType() == "bluekoopa" && !it->getMovingLeft() && (ev.time / 30) % 10 >= 5)
            gout << stamp(blueKoopaRightMoveTexture,500+it->getDistance()-mario.getDistance(),it->getPosition().y);
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
