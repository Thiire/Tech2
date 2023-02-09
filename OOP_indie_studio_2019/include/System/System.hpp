/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** System
*/

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "../Interface/ISystem.hpp"
#include "../Entity/Entity.hpp"
#include "../Storage/Storage.hpp"
#include "../Component/Component.hpp"
#include "../System/Event.hpp"
#include "../System/Menu.hpp"
#include "../System/Game.hpp"
#include "../System/Sound.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <cstdarg>
#include <fstream>
#include <algorithm>
#include <cmath>

class System : public ISystem {
    public:
        System();
        ~System();
        void start();
        irr::EKEY_CODE keyPress();

    protected:
    private:
        std::vector<Entity> _entities;
        std::vector<Storage> _stock;
        std::vector<irr::core::vector3df> _direction;
        std::vector<irr::core::vector3df> _way;
        size_t _idCounter;
        irr::IrrlichtDevice *_window;
        int _state;
        Event *event;
        Menu *menu;
        Game *game;
        Sound *sound;
        bool _newGame;
        bool _death;
        void checkVictory();
        void launchIA();
        void explosionTimer();
        void createMap(std::vector<std::string> map = {});
        void switchMap();
        void saveMap();
        void loadMap();
        void fillMap(std::vector<std::string> &map);
        void supEntity(size_t id);
        Ett::Type canDestroy(irr::core::vector3df pos);
        void dropBomb(Ett::Type controller, size_t botID = -1);
        void setParticle(irr::core::vector3df pos, int &state);
        bool canDrop(size_t id, irr::core::vector3df pos);
        void updateExplosion(irr::core::vector3df pos, Stat *stats);
        size_t getId(Cmp::Type type, Component *cmp);
        Ett::Type getType(size_t id);
        void setCollisions();
        void initBot(std::vector<bool> type);

        irr::core::vector3df getCenterPos(irr::core::vector3df coords);

        Component *getComponent(Cmp::Type type, size_t id);
        void supComponent(size_t id);
        bool hasComponent(Cmp::Type type, size_t id);
        void createWindow();
        void detectPowerUp();
        irr::scene::ISceneManager *_sceneMngr;
        template<typename T>
        std::vector<T *> getComponents(Cmp::Type type, int size...);
        template<typename ...Args>
        size_t addPlayer(Args ...args);
        template<typename ...Args>
        size_t addPlayer2(Args ...args);
        template<typename ...Args>
        size_t addBot(Args ...args);
        template<typename ...Args>
        size_t addPowerUp(Args ...args);
        template<typename ...Args>
        size_t addBox(Args ...args);
        template<typename ...Args>
        size_t addRamp(Args ...args);
        template<typename ...Args>
        size_t addWall(Args ...args);
        template<typename ...Args>
        size_t addPillar(Args ...args);
        template<typename ...Args>
        size_t addGround(Args ...args);
        template<typename ...Args>
        size_t addBomb(Args ...args);
        void playerMovements();
        bool checkCollision(irr::scene::IAnimatedMeshSceneNode* node1, irr::scene::IAnimatedMeshSceneNode* node2);
};

#endif /* !SYSTEM_HPP_ */