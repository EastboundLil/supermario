#ifndef MUSICBOX_H
#define MUSICBOX_H

#include <SFML/Audio.hpp>
#include <cstdlib>

class MusicBox
{
public:

    MusicBox()
    {
        folder = "music/";
    }

    void playMenuMusic()
    {
        int no = (rand() % 3) + 1;
        std::stringstream ss;
        ss << no;
        std::string track = ss.str();
        music.openFromFile(folder + "menu" + track + ".wav");
        music.setVolume(50);
        music.play();
    }

    void playOverworldMusic()
    {
        int no = (rand() % 2) + 1;
        std::stringstream ss;
        ss << no;
        std::string track = ss.str();
        music.openFromFile(folder + "overworld" + track + ".wav");
        music.setVolume(50);
        music.play();
    }

    void playUndergroundMusic()
    {
        int no = (rand() % 2) + 1;
        std::stringstream ss;
        ss << no;
        std::string track = ss.str();
        music.openFromFile(folder + "underground" + track + ".wav");
        music.setVolume(50);
        music.play();
    }

private:
    sf::Music music;
    std::string folder;

};


#endif // MUSICBOX_H
