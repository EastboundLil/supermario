#ifndef WINDOW_H
#define WINDOW_H



class Window
{
public:
    void generateLevel();
    std::list<Terrain*> getLevel();

private:

    //Mario mario;
    std::list<Terrain*> level;
};

#endif // WINDOW_H
