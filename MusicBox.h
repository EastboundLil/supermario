#ifndef MUSICBOX_H
#define MUSICBOX_H

#include <SFML/Audio.hpp>

class MusicBox
{
public:
    void play()
    {
        sf::SoundBuffer buffer;
        buffer.loadFromFile("music/menu.wav");
    }
};


#endif // MUSICBOX_H
