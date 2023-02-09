/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

#include "../../libs/include/irrlicht.h"
#include <iostream>
#include <cmath>

namespace Cmp {
    enum Type {
        UNDEFINED=-1,
        TIMER,
        MESH,
        CUBE,
        STAT,
    };
};

class IComponent {
    public:
        virtual ~IComponent() = default;
        virtual Cmp::Type getType() const = 0;

    protected:
    private:
};

#endif /* !ICOMPONENT_HPP_ */
