#include "Game.h"

Game::Game() :
    WINDOW_HEIGHT(600),
    WINDOW_WIDTH(1000),
    difficulty(1),
    character("mario")
{
    //gout.load_font("LiberationSans-Regular.tff",100,false);

    srand(time(NULL));
    gin.timer(1);
    gout.open(WINDOW_WIDTH,WINDOW_HEIGHT);
    gout.showmouse(false);

    mainMenu = { "newgame","difficulty","character","quit"};
    difficultyMenu = { "easy", "medium", "hard", "brutal" };
    characterMenu = { "mariohead","flashhead","empire" };

    tt = {  "life", "mariohead", "flashhead","empire",
            "menubackground","cursor", "newgame","difficulty","character","quit","easy","medium","hard","brutal","dlc",
            "background","ground","cliff","hillbegin","hill","hillend","mediumhillbegin","mediumhill","mediumhillend",
            "highhillbegin","highhill","highhillend","pipe","pipehelper","smallpipe","smallpipehelper","highpipe","highpipehelper",
            "end","endhelper","stair","stair2","stair3","stair4","stair5","castle","castlehelper"};
    et = {  "goomba","koopa","redkoopa","bluekoopa","yellowkoopa","blackkoopa","spiny","boo","piranhaplant"};
    mt = {  "mario","flash","vader"};

    numberOfTerrainTypes = tt.size();
    numberOfEnemieTypes = et.size();
    numberOfMarioTypes = mt.size();

    for(std::string s : tt)
        terrainTextureMap[s] = canvas();

    std::vector<canvas> c;
    c.push_back(canvas());
    c.push_back(canvas());
    c.push_back(canvas());
    c.push_back(canvas());

    std::vector<canvas> c2;
    c2.push_back(canvas());
    c2.push_back(canvas());
    c2.push_back(canvas());
    c2.push_back(canvas());
    c2.push_back(canvas());
    c2.push_back(canvas());

    for(std::string s : et)
    {
        enemyTextureMap[s] = c;
    }

    for(std::string s : mt)
    {
        marioTextureMap[s] = c2;
    }

    for(std::map<std::string,std::vector<canvas> >::iterator m = marioTextureMap.begin(); m != marioTextureMap.end(); m++)
    {
        LOG("first: " << m->first);
        readTexture(m->first,m->second.at(0),m->second.at(1),m->second.at(2),m->second.at(3));
        readTexture(m->first + "jump",m->second.at(4),m->second.at(5));
    };

    for(std::map<std::string,canvas>::iterator t = terrainTextureMap.begin(); t != terrainTextureMap.end(); t++)
        readTexture(t->first,t->second);
    for(std::map<std::string,std::vector<canvas> >::iterator e = enemyTextureMap.begin(); e != enemyTextureMap.end(); e++)
        readTexture(e->first,e->second.at(0),e->second.at(1),e->second.at(2),e->second.at(3));
}

bool Game::newGame()
{
    if(Mario::getInstance().getHealth() == -1) return false;

    bool died = false;
    bool win = false;
    Mario::getInstance().reset(WINDOW_WIDTH/2,0);
    generateLevel();
    movingRight = false;
    movingLeft = false;

    while(gin >> ev) {

        if(died)
        {
            Mario::getInstance().fall(WINDOW_HEIGHT+7000);
            if(Mario::getInstance().getHeight()+Mario::getInstance().getPosition().y == WINDOW_HEIGHT+7000) break;
        }
        else
        {
            if(ev.keycode == key_escape) return false;

            //int CURRENT_HEIGHT_L  = WINDOW_HEIGHT - level.at((Mario::getInstance().getDistance())/50)->getHeight();
            //int CURRENT_HEIGHT_R  = WINDOW_HEIGHT - level.at((Mario::getInstance().getDistance()+50)/50)->getHeight();
            int CURRENT_HEIGHT  = WINDOW_HEIGHT - level.at((Mario::getInstance().getDistance()+25)/50)->getHeight();
            int PREV_HEIGHT     = WINDOW_HEIGHT - level.at((Mario::getInstance().getDistance()/50))->getHeight();
            int NEXT_HEIGHT     = WINDOW_HEIGHT - level.at((Mario::getInstance().getDistance()/50)+1)->getHeight();

            if(ev.keycode == key_right)     movingRight = true;
            if(ev.keycode == -key_right)    movingRight = false;
            if(ev.keycode == key_left)      movingLeft = true;
            if(ev.keycode == -key_left)     movingLeft = false;
            if(ev.keycode == key_space)     Mario::getInstance().sprintOn();
            if(ev.keycode == -key_space)    Mario::getInstance().sprintOff();
            if(ev.keycode == key_up)        Mario::getInstance().jump();

            if(movingRight) Mario::getInstance().moveRight(NEXT_HEIGHT);
            if(movingLeft) Mario::getInstance().moveLeft(PREV_HEIGHT);
            Mario::getInstance().fall(CURRENT_HEIGHT);

            for(Enemy* it : enemies)
            {
                if(ev.keycode == key_up)
                    it->jump();
                it->move(WINDOW_HEIGHT - level.at(((it->getDistance())/50))->getHeight(),
                         WINDOW_HEIGHT - level.at(((it->getDistance())/50)+1)->getHeight());
                it->fall(WINDOW_HEIGHT - level.at((it->getDistance()+25)/50)->getHeight());
            }
            died = collided() || fallen();
            if(died)
            {
                Mario::getInstance().setSpeed(0);
                Mario::getInstance().jump();
            }
            win = Mario::getInstance().getDistance() == castleDistance-100;
            if(win) return false;
        }
        draw();
    }
    Mario::getInstance().decrementHealth();
    return true;
}

void Game::generateLevel()
{
    generateTerrain();
    generateEnemies();
}

void Game::generateTerrain()
{

    for(Terrain* it : level)
    {
        delete it;
    }
    level.clear();

    level.push_back(new Ground());
    level.push_back(new End());
    level.push_back(new EndHelper());

    for(int i = 0; i < 15; ++i)
    {
        level.push_back(new Ground());
    }

    for(int i = 0; i < difficulty*20; ++i)
    {
        addGround();

        int r = rand() % 9;
        switch(r){
            case 0: addPipe();      addGround(); break;
            case 1: addSmallPipe(); addGround(); break;
            case 2: addHighPipe();  addGround(); break;
            case 3: addCliff();     addGround(); break;
            case 4: addHill();      addGround(); break;
            case 5: addMediumHill();addGround(); break;
            case 6: addHighHill();  addGround(); break;
            case 7: addStair();     addGround(); break;
            case 8: addDownStair(); addGround(); break;
        }
    }

    level.push_back(new Castle()); castleDistance = level.size()*50;
    level.push_back(new CastleHelper());
    level.push_back(new CastleHelper());
    level.push_back(new CastleHelper());
    level.push_back(new CastleHelper());
    level.push_back(new Ground());
    level.push_back(new Ground());
    level.push_back(new Ground());
    level.push_back(new Ground());

}

void Game::addGround()
{
    int r = rand() % 5;
    for(int i = 0; i < r; i++)
    {
        level.push_back(new Ground());
    }
}

void Game::addPipe()
{
    int r = rand() % 3;
    for(int i = 1; i < r; i++)  level.push_back(new Ground());

    level.push_back(new Pipe());
    level.push_back(new PipeHelper());

    r = rand() % 3;
    for(int i = 0; i < r; i++)  level.push_back(new Ground());
}

void Game::addSmallPipe()
{
    int r = rand() % 3;
    for(int i = 1; i < r; i++)  level.push_back(new Ground());

    level.push_back(new SmallPipe());
    level.push_back(new SmallPipeHelper());

    r = rand() % 3;
    for(int i = 0; i < r; i++)  level.push_back(new Ground());
}

void Game::addHighPipe()
{
    int r = rand() % 3;
    for(int i = 1; i < r; i++)  level.push_back(new Ground());

    level.push_back(new Pipe());
    level.push_back(new PipeHelper());
    level.push_back(new HighPipe());
    level.push_back(new HighPipeHelper());

    r = rand() % 3;
    for(int i = 0; i < r; i++)  level.push_back(new Ground());
}

void Game::addCliff()
{
    int r = rand() % difficulty + 1;

    if(r < 3)
    {
        level.push_back(new Cliff());
        level.push_back(new Cliff());
        level.push_back(new Cliff());
    }
    else
    {
        for(int i=0; i < r; i++)
        {
            level.push_back(new Cliff());
            level.push_back(new Ground());
        }
    }
}

void Game::addHill()
{
    level.push_back(new HillBegin());
    int r = rand() % 6;
    for(int i=0; i < r; i++)
    {
        level.push_back(new Hill());
    }
    level.push_back(new HillEnd());
}

void Game::addMediumHill()
{
    level.push_back(new MediumHillBegin());
    int r = rand() % 6;
    for(int i=0; i < r; i++)
    {
        level.push_back(new MediumHill());
    }
    level.push_back(new MediumHillEnd());
}

void Game::addHighHill()
{
    level.push_back(new HighHillBegin());
    int r = rand() % 6;
    for(int i=0; i < r; i++)
    {
        level.push_back(new HighHill());
    }
    level.push_back(new HighHillEnd());
}

void Game::addStair()
{
    int r = rand() % difficulty+2;

    std::vector<Terrain*> stairs;
    stairs.push_back(new Stair());
    stairs.push_back(new Stair2());
    stairs.push_back(new Stair3());
    stairs.push_back(new Stair4());
    stairs.push_back(new Stair5());

    for(int i = 0; i < r; i++)
    {
        level.push_back(stairs.at(i));
    }
}

void Game::addDownStair()
{
    int r = rand() % 3;

    std::vector<Terrain*> stairs;
    stairs.push_back(new Stair());
    stairs.push_back(new Stair2());
    stairs.push_back(new Stair3());

    for(int i = r; i >= 0; i--)
    {
        level.push_back(stairs.at(i));
    }
}

std::vector<int> Game::posOfPipes()
{
    std::vector<int> posOfPipes;
    for(int i = 0; i < level.size(); i++)
    {
        if(level.at(i)->getType() == "pipe" ||
           level.at(i)->getType() == "lowpipe" ||
           level.at(i)->getType() == "highpipe")
        {
            posOfPipes.push_back(i);
        }
    }
    return posOfPipes;
}

void Game::generateEnemies()
{
    for(Enemy* it : enemies)
    {
        delete it;
    }
    enemies.clear();

    for(int i=0; i < difficulty*15; i++)
    {
        int r = rand() % numberOfEnemieTypes-4+difficulty;
        int temp = (level.size()*50) - castleDistance;
        int pos = (rand() % ((level.size()*50)-temp-700)) + 600;
        int pipe = rand() % posOfPipes().size();
        int height = WINDOW_HEIGHT - level.at(posOfPipes().at(pipe))->getHeight();
        pipe = posOfPipes().at(pipe)*50 + 17;

        switch(r){
            case 0: enemies.push_back(new Goomba(pos)); break;
            case 1: enemies.push_back(new PiranhaPlant(pipe,height));
                    enemies.push_back(new PiranhaPlant(pipe,height));break;
            case 2: enemies.push_back(new Koopa(pos)); break;
            case 3: enemies.push_back(new RedKoopa(pos)); break;
            case 4: enemies.push_back(new BlueKoopa(pos)); break;
            case 5: enemies.push_back(new YellowKoopa(pos)); break;
            case 6: enemies.push_back(new BlackKoopa(pos)); break;
            case 7: enemies.push_back(new Spiny(pos)); break;
            case 8: enemies.push_back(new Boo(pos)); break;

        }
    }
}

bool Game::collided()
{
    for(std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++)
    {
        if(Mario::getInstance().getDistance()+25 >= (*it)->getDistance()-25 &&
           Mario::getInstance().getDistance()-25 <= (*it)->getDistance()+25 &&
           Mario::getInstance().getPosition().y + Mario::getInstance().getHeight() <= (*it)->getPosition().y+10 &&
           Mario::getInstance().getPosition().y + Mario::getInstance().getHeight() >= (*it)->getPosition().y-10 &&
           Mario::getInstance().getSpeed() > 0 )
        {
            if((*it)->isThorned()) return true;
            else
            {
                (*it)->decrementHealth();
                if((*it)->getHealth() == 0)
                {
                    Mario::getInstance().addScore((*it)->getValue()*difficulty);
                    delete (*it);
                    enemies.erase(it);
                }
                Mario::getInstance().zeroSpeed();
                Mario::getInstance().jump();
            }
        }
        else if(Mario::getInstance().getDistance()+25 >= (*it)->getDistance()-25 &&
           Mario::getInstance().getDistance()-25 <= (*it)->getDistance()+25 &&
           Mario::getInstance().getPosition().y < (*it)->getPosition().y + (*it)->getHeight() &&
           Mario::getInstance().getPosition().y + Mario::getInstance().getHeight() > (*it)->getPosition().y)
        {
            return true;
        }
    }
    return false;
}

bool Game::fallen()
{
    return (Mario::getInstance().getPosition().y > WINDOW_HEIGHT);
}

void Game::run()
{
    PlaySound(TEXT("music/menu.wav"),NULL,SND_ASYNC);
    quitGame = false;
    cursor = 0;
    actualMenu = &mainMenu;
    while(gin >> ev && !quitGame) {
        if(ev.keycode == key_up)    if(cursor != 0) cursor--;
        if(ev.keycode == key_down)  if(cursor != actualMenu->size()-1) cursor++;
        if(ev.keycode == key_escape) actualMenu = &mainMenu;
        if(ev.keycode == key_enter) executeMenuElement();

        drawMenu();
        drawCursor();
        gout << refresh;
    }
}

void Game::drawMenu()
{
    terrainTextureMap["menubackground"].transparent(false);
    gout << stamp(terrainTextureMap["menubackground"],0,0);
    for(unsigned int i=0; i < actualMenu->size(); i++)
    {
        gout << stamp(terrainTextureMap[actualMenu->at(i)], (WINDOW_WIDTH/2)-100, 350+(i*50));
    }
}

void Game::drawCursor()
{
    gout << stamp(terrainTextureMap["cursor"], (WINDOW_WIDTH/2)-150, 350+(cursor*50));
}

void Game::executeMenuElement()
{
    if(actualMenu->at(cursor) == "newgame")         { Mario::getInstance().init(); PlaySound(TEXT("music/overworld.wav"),NULL,SND_ASYNC);while(newGame()); PlaySound(TEXT("music/menu.wav"),NULL,SND_ASYNC);}
    else if(actualMenu->at(cursor) == "difficulty") { actualMenu = &difficultyMenu; cursor = 0; }
    else if(actualMenu->at(cursor) == "character")  { actualMenu = &characterMenu; cursor = 0; }
    else if(actualMenu->at(cursor) == "quit")       quitGame = true;
    else if(actualMenu->at(cursor) == "easy")       { difficulty = 1; actualMenu = &mainMenu; cursor = 0; }
    else if(actualMenu->at(cursor) == "medium")     { difficulty = 2; actualMenu = &mainMenu; cursor = 0; }
    else if(actualMenu->at(cursor) == "hard")       { difficulty = 3; actualMenu = &mainMenu; cursor = 0; }
    else if(actualMenu->at(cursor) == "brutal")     { difficulty = 4; actualMenu = &mainMenu; cursor = 0; }
    else if(actualMenu->at(cursor) == "mariohead")      { character = "mario"; actualMenu = &mainMenu; cursor = 0; }
    else if(actualMenu->at(cursor) == "flashhead")      { character = "flash"; actualMenu = &mainMenu; cursor = 0; }
    else if(actualMenu->at(cursor) == "empire")      { character = "vader"; actualMenu = &mainMenu; cursor = 0; }
}

void Game::draw()
{
    drawBackgound();
    drawEnemies();
    drawLevel();
    drawMario();
    drawHud();

    gout << refresh;
}

void Game::drawBackgound()
{
    terrainTextureMap["background"].transparent(false);
    gout    << stamp(terrainTextureMap["background"],0,0);;
}

void Game::drawMario()
{
    if(Mario::getInstance().getSpeed() != 0 && movingRight)
        gout << stamp(marioTextureMap[character].at(5),Mario::getInstance().getPosition().x,Mario::getInstance().getPosition().y);
    else if(Mario::getInstance().getSpeed() != 0 && movingLeft)
        gout << stamp(marioTextureMap[character].at(4),Mario::getInstance().getPosition().x,Mario::getInstance().getPosition().y);
    else if(movingLeft && (ev.time / 30) % 10 < 5)
        gout << stamp(marioTextureMap[character].at(0),Mario::getInstance().getPosition().x,Mario::getInstance().getPosition().y);
    else if(movingLeft && (ev.time / 30) % 10 >= 5)
        gout << stamp(marioTextureMap[character].at(2),Mario::getInstance().getPosition().x,Mario::getInstance().getPosition().y);
    else if(movingRight && (ev.time / 30) % 10 < 5)
        gout << stamp(marioTextureMap[character].at(1),Mario::getInstance().getPosition().x,Mario::getInstance().getPosition().y);
    else if(movingRight && (ev.time / 30) % 10 >= 5)
        gout << stamp(marioTextureMap[character].at(3),Mario::getInstance().getPosition().x,Mario::getInstance().getPosition().y);
    else if(Mario::getInstance().getSpeed() != 0 && !Mario::getInstance().isMovingLeft())
        gout << stamp(marioTextureMap[character].at(5),Mario::getInstance().getPosition().x,Mario::getInstance().getPosition().y);
    else if(Mario::getInstance().getSpeed() != 0 && Mario::getInstance().isMovingLeft())
        gout << stamp(marioTextureMap[character].at(4),Mario::getInstance().getPosition().x,Mario::getInstance().getPosition().y);
    else if(Mario::getInstance().isMovingLeft())
        gout << stamp(marioTextureMap[character].at(0),Mario::getInstance().getPosition().x,Mario::getInstance().getPosition().y);
    else if(!Mario::getInstance().isMovingLeft())
        gout << stamp(marioTextureMap[character].at(1),Mario::getInstance().getPosition().x,Mario::getInstance().getPosition().y);
}

void Game::drawHud()
{
    std::string health,score;
    std::ostringstream temph,temps;
    temph<<Mario::getInstance().getHealth();
    health=temph.str();
    temps<<Mario::getInstance().getScore();
    score=temps.str();

    gout << stamp(terrainTextureMap["life"],50,20);
    gout << color(255,255,255);
    gout << move_to(110,40) << text("X ") << text(health);
    gout << move_to(160,40) << text("Score: ") <<text(score);
}

void Game::drawLevel()
{
    int offset = 500;
    for(Terrain *it : level)
    {
        if(it->getType() != "pipehelper" &&
           it->getType() != "smallpipehelper" &&
           it->getType() != "highpipehelper" &&
           it->getType() != "endhelper"  &&
           it->getType() != "cliff"      &&
           it->getType() != "castlehelper")
                drawTerrain(it->getType(),it->getHeight(),offset);
        offset += 50;
    }
}

void Game::drawTerrain(std::string type, int height, int offset)
{
    gout << stamp(terrainTextureMap[type], offset-Mario::getInstance().getDistance(),WINDOW_HEIGHT-height);
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
            gout << stamp(enemyTextureMap[type].at(0), 500 + distance - Mario::getInstance().getDistance(), y);
    else if(isMovingLeft && timer)
            gout << stamp(enemyTextureMap[type].at(1), 500 + distance - Mario::getInstance().getDistance(), y);
    else if(!isMovingLeft && !timer)
            gout << stamp(enemyTextureMap[type].at(2), 500 + distance - Mario::getInstance().getDistance(), y);
    else if(isMovingLeft && !timer)
            gout << stamp(enemyTextureMap[type].at(3), 500 + distance - Mario::getInstance().getDistance(), y);
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
