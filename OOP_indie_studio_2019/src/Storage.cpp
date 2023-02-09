/*
** EPITECH PROJECT, 2020
** Storage.cpp
** File description:
** Storage
*/

#include "../include/Storage/Storage.hpp"

Storage::Storage(Cmp::Type type)
{
    this->_type = type;
}

Storage::~Storage()
{
    for (size_t idx = 0; idx < this->store.size(); idx++) {
        delete this->store[idx];
    }
    this->store.clear();
    this->store_map.clear();
}

void Storage::resetStorage()
{
    for (size_t idx = 0; idx < this->store.size(); idx++) {
        delete this->store[idx];
    }
    this->store.clear();
    this->store_map.clear();
}

Cmp::Type Storage::getType() const
{
    return this->_type;
}

Component *Storage::getComponent(size_t id)
{
    if (this->store_map.find(id) != this->store_map.end()) {
        if (this->store.size() >= this->store_map[id]) {
            return this->store[this->store_map[id]];
        }
    }
}

bool Storage::hasComponent(size_t id)
{
    return store_map.find(id) != store_map.end();
}

void Storage::addMesh(size_t id, double x, double y, double z, const char *path, irr::scene::ISceneManager *sceneMngr, irr::core::vector3df scale, double rotx, double roty, double rotz, bool rotate, const char *texture)
{ 
    this->store.push_back(new Mesh(x, y, z, path, sceneMngr, rotx, roty, rotz, rotate, texture, scale));
    this->store_map[id] = this->store.size() - 1;
}

void Storage::addCube(size_t id, double x, double y, double z, irr::scene::ISceneManager *sceneMngr, irr::video::ITexture *texture)
{ 
    this->store.push_back(new Cube(x, y, z, sceneMngr, texture));
    this->store_map[id] = this->store.size() - 1;
}

void Storage::addStat(size_t id, int power, double speed)
{ 
    this->store.push_back(new Stat(power, speed));
    this->store_map[id] = this->store.size() - 1;
}

void Storage::addTimer(size_t id)
{ 
    this->store.push_back(new Timer());
    this->store_map[id] = this->store.size() - 1;
}

size_t Storage::getId(Component *obj)
{
    std::unordered_map<size_t, size_t>::iterator it;

    for (it = this->store_map.begin(); it != this->store_map.end(); it++) {
        if (obj == this->store[it->second]) {
            return it->first;
        }
    }
}

void Storage::supComponent(size_t id)
{
    int index = -1;
    std::unordered_map<size_t, size_t>::iterator it;

    for (it = this->store_map.begin(); it != this->store_map.end(); it++) {
        if (it->first == id) {
            index = it->second;
            if (this->store[index]) {
                delete this->store[index];
            }
            this->store.erase(this->store.begin() + index);
            this->store_map.erase(it);
            break;
        }
    }
    if (index == -1)
        return;
    for (it = this->store_map.begin(); it != this->store_map.end(); it++) {
        if (it->second > index) {
            it->second--;
        }
    }
}
