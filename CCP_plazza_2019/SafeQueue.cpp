/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** SafeQueue
*/

#include "SafeQueue.hpp"

SafeQueue::SafeQueue()
{
    this->_mutex = std::make_unique<std::mutex>();
}


void SafeQueue::push(Pizza<std::string, std::string> pizza)
{
    this->_pizzas.push_back(pizza);
}

bool SafeQueue::tryPop(Pizza<std::string, std::string> &pizza)
{
    if (!this->_mutex->try_lock())
        return false;
    if (this->_pizzas.empty()) {
        this->_mutex->unlock();
        return false;
    }
    pizza = this->_pizzas.back();
    this->_pizzas.pop_back();
    this->_mutex->unlock();
    return true;
}

const int SafeQueue::getSize() const
{
    return this->_pizzas.size();
}
