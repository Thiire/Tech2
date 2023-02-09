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
#include "../SafeQueue.hpp"
#include "../Pipe.hpp"
#include "../Kitchen.hpp"

class Recep {
    public:
        Recep(int multiplier, int cook = 5, int time = 2000);
        ~Recep();
        void start();
        void kitchenMessage();
        void addKitchen();
        int getNbCook() const;
        int getNbKitchen();
        bool checkKitchen();
        Pipe getPipe() const;
        std::vector<std::vector<Cook *>> &getKitchens();
        void setInput(std::string &str);
    protected:
    private:
        Pipe _pipe;
        int _multi;
        std::string _input;
        int _nb_cook;
        int _nbKitchen;
        int _time;
        std::vector<std::vector<Cook *>> _kitchens;
        SafeQueue _list;
        std::vector<bool> _status;
};

#endif /* !RECEP_HPP_ */
