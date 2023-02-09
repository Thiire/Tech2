/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** init
*/

#include "include/teams.h"

void init_cli(serv_t *serv)
{
    for (int a = 0; a < 255; a += 1) {
        serv->cli[a].isLogged = 0;
        serv->cli[a].cliFd = 0;
        memset(serv->cli[a].userName, 0, DEFAULT_NAME_LENGTH);
        serv->cli[a].user_uid = calloc(255, sizeof(char));
    }
}

void init_serv2(serv_t *serv)
{
    int opt = 1;

    init_cli(serv);
    serv->sd = 0;
    if ((serv->servFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("SOCKET ERROR");
        exit (84);
    }
    if (setsockopt(serv->servFd, SOL_SOCKET, SO_REUSEPORT, &opt,
    sizeof(opt)) < 0) {
        perror("setup_socket");
        close(serv->servFd);
        exit(84);
    }
    serv->users = getUsers();
}

void init_server(serv_t *serv, char **av)
{
    init_serv2(serv);
    serv->max_sd = 0;
    serv->servaddr.sin_family = AF_INET;
    serv->servaddr.sin_addr.s_addr = INADDR_ANY;
    serv->servaddr.sin_port = htons(atoi(av[1]));
    if ((bind(serv->servFd, (struct sockaddr *)&serv->servaddr, \
    sizeof(serv->servaddr))) != 0) {
        perror("BIND ERROR");
        close(serv->servFd);
        exit (84);
    }
    if ((listen(serv->servFd, 5)) != 0) {
        perror("LISTEN ERROR");
        close(serv->servFd);
        exit(84);
    }
    serv->len = sizeof(serv->servaddr);
}

void init_fct(serv_t *serv)
{
    serv->features[0] = &login;
    serv->features[1] = &logout;
    serv->features[2] = &help;
    serv->features[3] = &users;
    serv->features[4] = &user;
}