/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Component
*/

#include "../include/Component/Component.hpp"

Component::Component(Cmp::Type type)
{
    this->_type = type;
}

Component::~Component()
{
}

Cmp::Type Component::getType() const
{
    return this->_type;
}
