#include "Game.h"

Game::Game() :
    WINDOW_HEIGHT(600),
    WINDOW_WIDTH(1000)
{
    gout.open(WINDOW_WIDTH,WINDOW_HEIGHT);
    readBackgroundTexture();
    readGroundTexture();

    //backgroundTexture = readTexture("pics/background.kep");
    //groundTexture = readTexture("pics/ground.kep");
    //marioTexture = readTexture("pics/ground.kep");
}

void Game::run()
{
    generateLevel();
    draw();

    while(gin >> ev && ev.keycode != key_escape) {
    }

}

void Game::draw()
{
    int i = 0;
    LOG("level size: " << level.size());

    drawBackgound();
    //drawMario();

    int offset = 0;
    for(Terrain *it : level)
    {
        LOG(++i << ". iteration");
        if(it->getWidget().getType() == "ground")
        {
            gout << stamp(groundTexture, 0+offset,WINDOW_HEIGHT-50);
        }

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
    //gout    << move_to(mario.getPosition().x,mario.getPosition().y)
    //        << stamp(mario.getWidget().getCanvas(),mario.getPosition().x,mario.getPosition().y);
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

void Game::generateLevel()
{
    //srand(time(NULL));

    for(int i = 0; i < 20; ++i)
    {
        level.push_back(new Ground("ground"));
        LOG("Terrain " << i+1 << " created");
    }
    LOG("level size: " << level.size());
}
