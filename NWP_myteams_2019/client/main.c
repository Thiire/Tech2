/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** main
*/

#include "./include/client.h"

void usage()
{
    printf("USAGE: ./myteams_cli ip port\n"
    "\tip\tis the server ip address on which the server socket listens\n"
    "\tport\tis the port number on which the server socket listens\n");
    exit(0);
}

int is_valable(char *str)
{
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '-')
            continue;
        if (str[i] == '.')
            continue;
        if (str[i] < '0' || str[i] > '9')
            return (84);
    }
    return (0);
}

int main(int ac, char **av)
{
    int check_ip = 0;
    int check_port = 0;

    if (ac != 3) {
        if (strcmp(av[1], "-help") == 0 && ac == 2)
            usage();
        return (84);
    }
    check_ip = is_valable(av[1]);
    check_port = is_valable(av[2]);
    if (check_ip == 84 || check_port == 84)
        return (84);
    start_client(atoi(av[2]), av[1]);
    return (0);
}