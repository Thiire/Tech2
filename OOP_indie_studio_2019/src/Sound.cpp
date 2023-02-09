/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Sound
*/

#include "../include/System/Sound.hpp"

void Sound::playMusic()
{
    this->play.play();
}

void Sound::playSound()
{
    this->sound.play();
}

Sound::Sound()
{
    this->play.openFromFile("./Assets/Sound/play.ogg");
    this->play.setVolume(30);
    this->play.setLoop(true);
    this->sb.loadFromFile("./Assets/Sound/Boom.ogg");
    this->sound.setBuffer(this->sb);
}

Sound::~Sound()
{
    this->play.setLoop(false);
    this->play.stop();
    this->sound.stop();
}
