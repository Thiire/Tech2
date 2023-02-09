/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** main
*/

#include "myftp.h"

char *my_strcat(char *str1, char *str2)
{
    char *res = malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 3));
    int i = 0;

    if (str1 == NULL || str2 == NULL)
        return (NULL);
    for (i = 0; str1[i] != '\0'; i++)
        res[i] = str1[i];
    for (int j = 0; str2[j] != '\0'; j++, i++)
        res[i] = str2[j];
    res[i] = '\0';
    return (res);
}

int init_server(int port, char *path)
{
    serv_t my_server;
    int new_socket = 0;
    int c_stock[100];
    int c_socket[100];

    my_server.max_sd = 0;
    my_server.socket = 0;
    for (int i = 0; i < 100; i++) {
        c_socket[i] = 0;
        c_stock[i] = 0;
    }
    my_server.socket = setup_server(my_server, port);
    loop(my_server, c_socket, c_stock, new_socket);
    return (0);
}

void help(void)
{
    printf("USAGE: ./myftp port path\n\tport\tis the port number on which "
    "the server socket listens\n\tpath\tis the path to the home directory "
    "for the Anonymous user\n");
}

int main(int ac, char **av)
{
    if (ac == 1)
        help();
    if (ac != 3) {
        if (ac == 2 && strncmp(av[1], "-help", 6) == 0) {
            help();
            return (0);
        } else
            return (84);
    }
    for (size_t i = 0; i < strlen(av[1]); i++) {
        if (av[1][i] == '-')
            continue;
        if (av[1][i] > '9' || av[1][i] < '0')
            return (84);
    }
    if (chdir(av[2]) == -1) {
        perror("chdir");
        return (84);
    }
    return (init_server(atoi(av[1]), av[2]));
}