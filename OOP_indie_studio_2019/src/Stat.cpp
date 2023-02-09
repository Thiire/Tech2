/*
** EPITECH PROJECT, 2020
** Stat.cpp
** File description:
** Stat
*/

#include "../include/Component/Stat.hpp"

Stat::Stat(int power, double speed) : Component(Cmp::Type::STAT)
{
    this->_power = power;
    this->_speed = speed;
}

Stat::~Stat()
{
}


void Stat::addStat(Stat *other)
{
    this->_power += other->getPower();
    this->_speed += other->getSpeed();
}

int Stat::getPower() const
{
    return this->_power;
}

float Stat::getSpeed() const
{
    return this->_speed;
}

void Stat::setPower(int power)
{
    this->_power = power;
}

void Stat::setSpeed(double &speed)
{
    this->_speed = speed;
}