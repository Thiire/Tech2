/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IEntity
*/

#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include <iostream>
#include <random>
#include <string>

namespace Ett {
    enum Type {
        UNDEFINED=-1,
        PLAYER,
        PLAYER2,
        BOT,
        BOMB,
        BOX,
        GROUND,
        WALL,
        PILLAR,
        RAMP,
        POWERUP
    };
};

class IEntity {
    public:
        virtual ~IEntity() = default;
        virtual size_t getID() const = 0;
        virtual Ett::Type getType() const = 0;

    protected:
    private:
};

#endif /* !IENTITY_HPP_ */
