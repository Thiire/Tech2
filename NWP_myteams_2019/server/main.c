/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** main
*/

#include "include/teams.h"
#include "../parser/include/parser.h"

void usage()
{
    printf("USAGE: ./myteams_server port\n\n"
    "\tport\tis the port number on which the server socket listens.\n");
    exit(0);
}

int main(int ac, char **av)
{
    if (ac != 2) {
        return (84);
    }
    if (strcmp(av[1], "-help") == 0)
        usage();
    for (size_t i = 0; i < strlen(av[1]); i++) {
        if (av[1][i] == '-')
            continue;
        if (av[1][i] < '0' || av[1][i] > '9')
            return (84);
    }
    start_server(av);
    return (0);
}