/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Entity
*/

#include "../include/Entity/Entity.hpp"

Entity::Entity(size_t id, Ett::Type type)
{
    this->_ID = id;
    this->_type = type;
}

size_t Entity::getID() const
{
    return this->_ID;
}

Ett::Type Entity::getType() const
{
    return this->_type;
}

void Entity::setType(Ett::Type type)
{
    this->_type = type;
}