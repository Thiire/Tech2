/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include "Pipe.hpp"
#include "Cook.hpp"
#include <cstdio>
#include <fstream>
#include <ctime>

class Kitchen {
    public:
        Kitchen(Pipe &pipe, int multiplier, int cook, int time);
        ~Kitchen();
        void start();
        void writeFile(const std::string &fileName, const std::string &msg);

    protected:
    private:
        int _multi;
        int _nb_cook;
        int _time;
        Pipe _pipe;
        std::vector<Cook *> _cooks;
        std::clock_t _clock;
        double _duration;
        bool resetClock();
        bool askPizza();
        bool askState();
};

#endif /* !KITCHEN_HPP_ */
