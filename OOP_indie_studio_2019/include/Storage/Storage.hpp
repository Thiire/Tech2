/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Storage
*/

#ifndef STORAGE_HPP_
#define STORAGE_HPP_

#include "../Component/Component.hpp"
#include "../Component/Mesh.hpp"
#include "../Component/Cube.hpp"
#include "../Component/Stat.hpp"
#include "../Component/Timer.hpp"
#include <memory>
#include <map>
#include <unordered_map>
#include <vector>
#include <cstdarg>

class Storage {
    public:
        Storage(Cmp::Type type);
        ~Storage();
        void resetStorage();
        size_t getId(Component *obj);
        Cmp::Type getType() const;
        Component *getComponent(size_t id);
        bool hasComponent(size_t id);
        void addMesh(size_t id, double x, double y, double z, const char *path, irr::scene::ISceneManager *sceneMngr, irr::core::vector3df scale = irr::core::vector3df{100.0f, 100.0f, 100.0f}, double rotx = 0.0, double roty = 0.0, double rotz = 0.0, bool rotate = false, const char *texture = NULL);
        void addCube(size_t id, double x, double y, double z, irr::scene::ISceneManager *sceneMngr, irr::video::ITexture *texture);
        void addStat(size_t id, int power, double speed);
        void addTimer(size_t id);
        void supComponent(size_t id);
        
    protected:
    private:
        Cmp::Type _type;
        std::vector<Component*> store;
        std::unordered_map<size_t, size_t> store_map;
};

#endif /* !STORAGE_HPP_ */
