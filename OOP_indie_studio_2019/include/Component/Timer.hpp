/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Timer
*/

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include "Component.hpp"
#include "chrono"

class Timer : public Component {
    public:
        Timer();
        ~Timer();
        std::chrono::high_resolution_clock::time_point getTime() const;
        void setTime(std::chrono::high_resolution_clock::time_point time);
        double getEllapsedTime() const;
        void resetTime();
    protected:
    private:
        std::chrono::high_resolution_clock::time_point _time;
};

#endif /* !TIMER_HPP_ */
