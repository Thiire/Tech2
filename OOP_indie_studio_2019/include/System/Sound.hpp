/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <vector>

class Sound {
    public:
        Sound();
        ~Sound();
        void playMusic();
        void playSound();
    protected:
    private:
        sf::Sound sound;
        sf::SoundBuffer sb;
        sf::Music play;
};

#endif /* !SOUND_HPP_ */
