/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include "../Interface/IComponent.hpp"
#include <string>

class Component : public IComponent {
    public:
        Component(Cmp::Type type = Cmp::UNDEFINED);
        ~Component();
        Cmp::Type getType() const final;

    protected:
    private:
        Cmp::Type _type;
};

#endif /* !COMPONENT_HPP_ */
