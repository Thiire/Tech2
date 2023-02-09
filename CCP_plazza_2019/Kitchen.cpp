/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Kitchen::Kitchen(Pipe &pipe, int multiplier, int cook, int time)
{
    this->_pipe = pipe;
    this->_multi = multiplier;
    this->_nb_cook = cook;
    this->_time = time;
    this->_pipe.closeParent();
    this->_clock = std::clock();
    for (int idx = 0; idx < this->_nb_cook; idx++) {
        this->_cooks.push_back(new Cook(this->_multi, this->_time, this->_pipe.getSize(), idx));
    }
}

Kitchen::~Kitchen()
{
}

void Kitchen::writeFile(const std::string &fileName, const std::string &msg)
{
    std::ofstream file;
    file.open(fileName, std::ios::app);
    file << msg;
    file.close();
}

void Kitchen::start()
{
    std::string input = "";
    std::string tmp = "";

    std::cout << "[" << this->_pipe.getSize() << "] " << "Opening kitchen" << std::endl;
    while (1) {
        this->askState();
        usleep(100);
        this->askPizza();
        this->resetClock();
        this->_duration = (std::clock() - this->_clock) / (double)CLOCKS_PER_SEC;
        if (this->_duration >= 1) {
            tmp = std::to_string(this->_pipe.getChild()) + " Kill me";
            this->_pipe << tmp;
            input = std::to_string(this->_pipe.getChild());
            this->_pipe >> input;
            if (!input.empty() && !input.compare(input.find(" ") + 1, 4, "STOP")) {
                std::cout << "[" << this->_pipe.getSize() << "] " << "No more work, Kitchen closed" << std::endl;
                break;
            } else {
                std::cout << "[" << this->_pipe.getSize() << "] " << "Force closed no one read" << std::endl;
                break;
            }
            this->_clock = std::clock();
        }
    }
}

bool Kitchen::resetClock()
{
    for (int idx = 0; idx < this->_cooks.size(); idx++) {
        if (!this->_cooks[idx]->isAvailable()) {
            this->_clock = std::clock();
            return true;
        }
    }
    return false;
}

bool Kitchen::askPizza()
{
    std::string input = "";
    std::string tmp = "";
    int idx = 0;

    for (; idx < this->_cooks.size(); idx++) {
        if (this->_cooks[idx]->isAvailable()) {
            tmp = std::to_string(this->_pipe.getChild()) + " need Pizza";
            this->_pipe << tmp;
            input = std::to_string(this->_pipe.getChild());
            this->_pipe >> input;
            break;
        }
    }
    if (input.empty() || !input.compare(input.find(" ") + 1, 8, "no Pizza")) {
        return false;
    } else {
        Pizza<std::string, std::string> tmp(std::stoi(input.substr(input.find(" ") + 1)), std::stoi(input.substr(input.find_last_of(" ") + 1)));
        this->_cooks[idx]->makePizza(tmp);
    }
    return false;
}

bool Kitchen::askState()
{
    std::string input = "";
    std::string tmp = "";
    int idx = 0;
    int stock = 0;

    tmp = std::to_string(this->_pipe.getChild()) + " need State ?";
    this->_pipe << tmp;
    input = std::to_string(this->_pipe.getChild());
    this->_pipe >> input;
    if (input.empty() || !input.compare(input.find(" ") + 1, 7, "no Need")) {
        return false;
    } else {
        std::cout << "[" << this->_pipe.getSize() << "] " << "State of Kitchen:" << std::endl;
        for (; idx < this->_cooks.size(); idx++) {
            if (!this->_cooks[idx]->isAvailable()) {
                std::cout << "    {" << idx << "} => " << this->_cooks[idx]->getPizza() << std::endl;
                stock++;
            }
        }
        if (stock == 0) {
            std::cout << "    => " << "This kitchen is empty." << std::endl;
        }
    }
    return false;
}
