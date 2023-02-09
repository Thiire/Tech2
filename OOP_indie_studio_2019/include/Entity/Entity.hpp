/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "../Interface/IEntity.hpp"

class Entity : public IEntity {
    public:
        Entity(size_t id, Ett::Type type);
        size_t getID() const final;
        Ett::Type getType() const final;
        void setType(Ett::Type type);

    protected:
    private:
        size_t _ID;
        Ett::Type _type;
};

#endif /* !ENTITY_HPP_ */
