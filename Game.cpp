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
        int PREV_HEIGHT     = WINDOW_HEIGHT - level.at((mario.getDistance()/50)-1)->getHeight();
        int NEXT_HEIGHT     = WINDOW_HEIGHT - level.at((mario.getDistance()/50)+1)->getHeight();

        if(ev.keycode == key_right)     movingRight = true;
        if(ev.keycode == -key_right)    movingRight = false;
        if(ev.keycode == key_left)      movingLeft = true;
        if(ev.keycode == -key_left)     movingLeft = false;
        if(ev.keycode == key_up)        mario.jump();
        if(ev.type == ev_timer)
        {
            if(movingRight) mario.moveRight(NEXT_HEIGHT);
            if(movingLeft) mario.moveLeft(PREV_HEIGHT);
            mario.fall(CURRENT_HEIGHT);
        }

        draw();
        if(mario.getPosition().y > WINDOW_HEIGHT) endLevel = true;
    }
    return true;
}

void Game::run()
{
    while(newGame())
    {
    }
}

void Game::draw()
{
    int i = 0;

    drawBackgound();
    drawMario();

    int offset = 500;
    for(Terrain *it : level)
    {
        if(it->getType() == "ground") gout << stamp(groundTexture, offset-mario.getDistance(),WINDOW_HEIGHT-it->getHeight());
        else if(it->getType() == "pipe") gout << stamp(pipeTexture, offset-mario.getDistance(),WINDOW_HEIGHT-it->getHeight());
        else if(it->getType() == "end") gout << stamp(groundTexture, offset-mario.getDistance(),WINDOW_HEIGHT-it->getHeight());

        offset += 50;
    }

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
    else if(mario.getSpeed() != 0)
        gout << stamp(marioJumpRightTexture,mario.getPosition().x,mario.getPosition().y);
    else gout << stamp(marioRightTexture,mario.getPosition().x,mario.getPosition().y);

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

void Game::generateLevel()
{

    for(Terrain* it : level)
    {
        delete it;
    }
    level.clear();

    //srand(time(NULL));
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
}
