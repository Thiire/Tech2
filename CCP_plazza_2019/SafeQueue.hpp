/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** SafeQueue
*/

#ifndef SAFEQUEUE_HPP_
#define SAFEQUEUE_HPP_

#include <thread>
#include <mutex>
#include <iostream>
#include <memory>
#include <vector>
#include "ISafeQueue.hpp"

class SafeQueue : public ISafeQueue {
    public:
        SafeQueue();
        void push(Pizza<std::string, std::string> pizza) final;
        bool tryPop(Pizza<std::string, std::string> &pizza) final;
        const int getSize() const final;


    protected:
    private:
        std::vector<Pizza<std::string, std::string>> _pizzas;
        std::unique_ptr<std::mutex> _mutex;
};

#endif /* !SAFEQUEUE_HPP_ */
