/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "../../libs/include/irrlicht.h"
#include "../../libs/include/driverChoice.h"
#include <vector>
#include <chrono>
#include <tuple>
#include <iostream>

class Game {
    public:
        Game(irr::IrrlichtDevice *win);
        ~Game();
        void displayGame(int state);
        void fixCamera(int x_start, int y_start, int x, int y);
        void rotateCamera(float rot);
        irr::scene::ISceneManager *getSceneManager() const;
        irr::video::IVideoDriver *getVideoDriver() const;
        void explosionParticle(float x, float y, float z);
    protected:
    private:
        std::vector<std::tuple<irr::scene::IParticleSystemSceneNode *, irr::scene::IParticleEmitter *, std::chrono::system_clock::time_point> > _particles;
        irr::IrrlichtDevice *_window;
        irr::scene::ISceneManager *_sceneMngr;
        irr::scene::ICameraSceneNode *_camera;
        irr::scene::ITerrainSceneNode *_floor;
        irr::video::IVideoDriver* _driver;
        irr::scene::ILightSceneNode *_sun;
        irr::scene::ISceneNode* _skydome;

        irr::core::vector3df _centerCamera;

        int size;
        float rotation;
        float m_rotation;
        int high;
};

#endif /* !GAME_HPP_ */
