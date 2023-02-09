/*
** EPITECH PROJECT, 2020
** Timer.cpp
** File description:
** Timer
*/

#include "../include/Component/Timer.hpp"

Timer::Timer() : Component(Cmp::Type::TIMER)
{
    this->_time = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
}

std::chrono::high_resolution_clock::time_point Timer::getTime() const
{
    return this->_time;
}

void Timer::setTime(std::chrono::high_resolution_clock::time_point time)
{
    this->_time = time;
}

double Timer::getEllapsedTime() const
{
    return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - this->_time).count();
}

void Timer::resetTime()
{
    this->_time = std::chrono::high_resolution_clock::now();
}