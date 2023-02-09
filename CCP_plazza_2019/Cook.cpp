/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#include "Cook.hpp"

bool CookPizza(std::unique_ptr<std::mutex> &mtx, Pizza<std::string, std::string> &pizza, int multi, int kitchen, int cook)
{
    if (pizza.getSize() == -1 || pizza.getType() == -1)
        return false;
    if (!mtx->try_lock()) {
        return false;
    }
    std::cout << "[" << kitchen << "] Cook " << cook << ", Making a Pizza..." << std::endl;
    switch (pizza.getType()) {
        case 1:
            std::this_thread::sleep_for(std::chrono::seconds(2) * multi);
            break;
        case 2:
            std::this_thread::sleep_for(std::chrono::seconds(1) * multi);
            break;
        case 4:
            std::this_thread::sleep_for(std::chrono::seconds(2) * multi);
            break;
        case 8:
            std::this_thread::sleep_for(std::chrono::seconds(4) * multi);
            break;
        default:
            break;
    }
    std::cout << "\t" << "[" << kitchen << "] Cook " << cook << ", Pizza Baked => " << pizza.getTypeStr() << " " << pizza.getSizeStr() << std::endl;
    mtx->unlock();
    return true;
}

void Cook::makePizza(Pizza<std::string, std::string> &pizza)
{

    this->_pizza = pizza;
    this->_cook = new std::thread(CookPizza, std::ref(this->_mutex), std::ref(this->_pizza), this->_multi, this->_kitchen, this->_idx);
    if (this->_cook->joinable()) {
        this->_cook->detach();
        usleep(1000);
    } else {
        std::cout << "not joinable" << std::endl;
    }
}

std::string Cook::getPizza()
{
    std::string piSize = this->_pizza.getSizeStr();
    std::string piType = this->_pizza.getTypeStr();

    return piType + " " + piSize;
}

bool Cook::isAvailable()
{
    if (this->_mutex->try_lock()) {
        this->_mutex->unlock();
        return true;
    }
    return false;
}

Cook::Cook(int multiplier, int time, int kitchen, int cook) : _pizza(-1, -1)
{
    this->_multi = multiplier;
    this->_time = time;
    this->_kitchen = kitchen;
    this->_idx = cook;
    this->isFinished = true;
    this->_mutex = std::make_unique<std::mutex>();
}

Cook::~Cook()
{
}
