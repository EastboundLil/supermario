#ifndef MUSICBOX_H
#define MUSICBOX_H

#include <SFML/Audio.hpp>
#include <cstdlib>
#include <sstream>

class MusicBox
{
public:

    MusicBox();

    void playMenuMusic();
    void playOverworldMusic();
    void playUndergroundMusic();

    void playJumpSound();
    void playOneUpSound();
    void playKillSound();
    void playDeathSound();
    void playMenuSound();
    void playBigMushroomSound();
    void playDamageSound();

private:
    sf::Music music;
    sf::SoundBuffer jumpBuffer;
    sf::SoundBuffer oneUpBuffer;
    sf::SoundBuffer killBuffer;
    sf::SoundBuffer deathBuffer;
    sf::SoundBuffer menuBuffer;
    sf::SoundBuffer bigMushroomBuffer;
    sf::SoundBuffer damageBuffer;

    sf::Sound jumpSound;
    sf::Sound oneUpSound;
    sf::Sound killSound;
    sf::Sound deathSound;
    sf::Sound menuSound;
    sf::Sound bigMushroomSound;
    sf::Sound damageSound;

    std::string folder;

};


#endif // MUSICBOX_H
