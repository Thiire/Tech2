/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ISafeQueue
*/

#ifndef ISAFEQUEUE_HPP_
#define ISAFEQUEUE_HPP_

#include "Pizza.hpp"

class ISafeQueue {
    public:
        virtual ~ISafeQueue() = default;
        virtual void push(Pizza<std::string, std::string> pizza) = 0;
        virtual bool tryPop(Pizza<std::string, std::string> &pizza) = 0;
        virtual const int getSize() const = 0;

    protected:
    private:
};

#endif /* !ISAFEQUEUE_HPP_ */
