/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** main
*/

#include "Graphic.hpp"
#include <signal.h>

void usage()
{
    std::cout << "USAGE:\ty'en as pas <3" << std::endl;
}

int main(int ac, char **av)
{
    int flag;

    if (ac != 4) {
        if (av[1] == "-help" && ac == 2) {
            usage();
            return 0;
        } else
            return 84;
    }
    try {
        flag = fcntl(0, F_GETFL);
        if (fcntl(0, F_SETFL, flag | O_NONBLOCK) < 0) {
            exit (84);
        }
        Graphic graph(std::stoi(av[1]), std::stoi(av[2]), std::stoi(av[3]));
        graph.start();
    } catch (std::exception &e) {
        std::cerr << "Error => " << e.what() << std::endl;
        return 84;
    }
    return 0 ;
}