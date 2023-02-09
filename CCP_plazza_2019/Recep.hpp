/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Recep
*/

#ifndef RECEP_HPP_
#define RECEP_HPP_

#include <thread>
#include <mutex>
#include <iostream>
#include <memory>
#include <vector>
#include <unistd.h>
#include <string.h>
#include "SafeQueue.hpp"
#include "Pipe.hpp"
#include "Kitchen.hpp"

class Recep {
    public:
        Recep(int multiplier, int cook = 5, int time = 2000);
        ~Recep();
        void start();
        void kitchenMessage();
        void addKitchen();
        int getNbCook() const;
        bool checkKitchen();
    protected:
    private:
        int _multi;
        Pipe _pipe;
        int _nb_cook;
        int _time;
        SafeQueue _list;
        std::vector<bool> _status;
};

#endif /* !RECEP_HPP_ */
