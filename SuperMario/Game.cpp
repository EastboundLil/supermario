#include "Game.h"

Game::Game() :
    WINDOW_HEIGHT(600),
    WINDOW_WIDTH(1000)
{
    gout.open(WINDOW_WIDTH,WINDOW_HEIGHT);
    backgroundTexture = readTexture("pics/background.kep");
    //groundTexture = readTexture("pics/ground.kep");
    //marioTexture = readTexture("pics/ground.kep");
}

void Game::run()
{
    //generateLevel();
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

        gout << stamp(it->getWidget().getCanvas(), 0+offset,WINDOW_HEIGHT-100);

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
    gout    << move_to(mario.getPosition().x,mario.getPosition().y)
            << stamp(mario.getWidget().getCanvas(),mario.getPosition().x,mario.getPosition().y);
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

void Game::generateLevel()
{
    //srand(time(NULL));

    for(int i = 0; i < 20; ++i)
    {
        level.push_back(new Ground(groundTexture));
        LOG("Terrain " << i+1 << " created");
    }
    LOG("level size: " << level.size());
}
