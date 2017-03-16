#include "MusicBox.h"

MusicBox::MusicBox()
{
    folder = "music/";

    jumpBuffer.loadFromFile         (folder + "jump.wav");
    oneUpBuffer.loadFromFile        (folder + "1up.wav");
    killBuffer.loadFromFile         (folder + "kill.wav");
    deathBuffer.loadFromFile        (folder + "death.wav");
    menuBuffer.loadFromFile         (folder + "menu.wav");
    bigMushroomBuffer.loadFromFile  (folder + "bigmushroom.wav");
    damageBuffer.loadFromFile       (folder + "damage.wav");

    jumpSound.setBuffer         (jumpBuffer);
    oneUpSound.setBuffer        (oneUpBuffer);
    killSound.setBuffer         (killBuffer);
    deathSound.setBuffer        (deathBuffer);
    menuSound.setBuffer         (menuBuffer);
    bigMushroomSound.setBuffer  (bigMushroomBuffer);
    damageSound.setBuffer       (damageBuffer);
}

void MusicBox::playJumpSound()          {jumpSound.play();}
void MusicBox::playOneUpSound()         {oneUpSound.play();}
void MusicBox::playKillSound()          {killSound.play();}
void MusicBox::playDeathSound()         {deathSound.play();}
void MusicBox::playMenuSound()          {menuSound.play();}
void MusicBox::playBigMushroomSound()   {bigMushroomSound.play();}
void MusicBox::playDamageSound()        {damageSound.play();}

void MusicBox::playMenuMusic()
{
    int no = (rand() % 3) + 1;
    std::stringstream ss;
    ss << no;
    std::string track = ss.str();
    music.openFromFile(folder + "menu" + track + ".wav");
    music.play();
}

void MusicBox::playOverworldMusic()
{
    int no = (rand() % 2) + 1;
    std::stringstream ss;
    ss << no;
    std::string track = ss.str();
    music.openFromFile(folder + "overworld" + track + ".wav");
    music.play();
}

void MusicBox::playUndergroundMusic()
{
    int no = (rand() % 2) + 1;
    std::stringstream ss;
    ss << no;
    std::string track = ss.str();
    music.openFromFile(folder + "underground" + track + ".wav");
    music.play();
}
