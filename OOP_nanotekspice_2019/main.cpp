/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** main
*/

#include <fstream>
#include <iostream>
#include <csignal>
#include "Data.hpp"

bool Data::prompt = false;

void signalHandler(int signal)
{
    if (signal == 2) {
        std::cout << std::endl;
        Data::prompt = false;
    }
}

int main(int ac, char **av)
{
    Data data;
    std::string user_input;
    signal(SIGINT, signalHandler);

    if (!av[1])
        return (84);
    data.parsefile_chipsets(av[1]);
    data.parsefile_links(av[1]);
    data.parse_input(av, ac);
    data.simulate();
    data.print_output();
    while (user_input.compare("exit") != 0) {
        if (Data::prompt == false) {
            std::cout << "> ";
        }
        std::cin >> user_input;
        if (user_input.compare("dump") == 0) {
            data.print_all();
        }
        if (user_input.compare("loop") == 0) {
            Data::prompt = true;
        }
        if (user_input.compare("display") == 0) {
            data.print_output();
        }
        if (user_input.compare("simulate") == 0) {
            data.simulate();
        }
        if (user_input.find("=") < user_input.size() && user_input.find("=") != 0) {
            data.change_input(user_input);
        }
    }
    return (0);
}