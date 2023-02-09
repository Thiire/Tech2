/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Stat
*/

#ifndef STAT_HPP_
#define STAT_HPP_

#include "Component.hpp"

class Stat : public Component {
    public:
        Stat(int power = 0, double speed = 1.0);
        ~Stat();
        void addStat(Stat *other);
        int getPower() const;
        float getSpeed() const;
        void setPower(int power);
        void setSpeed(double &speed);
    protected:
    private:
        int _power;
        float _speed;
};

#endif /* !STAT_HPP_ */
