/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#ifndef COOK_HPP_
#define COOK_HPP_

#include "Pizza.hpp"
#include <memory>
#include <thread>
#include <mutex>
#include "unistd.h"

bool CookPizza(std::unique_ptr<std::mutex> &mtx, Pizza<std::string, std::string> &pizza, int multi, int kitchen, int cook);

class Cook {
    public:
        Cook(int multiplier, int time, int kitchen, int cook);
        ~Cook();
        bool isAvailable();
        void makePizza(Pizza<std::string, std::string> &pizza);
        std::string getPizza();

    protected:
    private:
        int _multi;
        bool isFinished;
        int _time;
        int _kitchen;
        int _idx;
        Pizza<std::string, std::string> _pizza;
        std::thread *_cook;
        std::unique_ptr<std::mutex> _mutex;
};

#endif /* !COOK_HPP_ */
