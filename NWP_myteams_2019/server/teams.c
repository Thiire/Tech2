/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** teams
*/

#include "include/teams.h"

void set_socket(serv_t *serv)
{
    FD_ZERO(&serv->readfds);
    FD_SET(serv->servFd, &serv->readfds);
    serv->max_sd = serv->servFd;
    for (int i = 0; i < 255; i += 1) {
        serv->sd = serv->cli[i].cliFd;
        if (serv->sd > 0)
            FD_SET(serv->sd, &serv->readfds);
        if (serv->sd > serv->max_sd)
            serv->max_sd = serv->sd;
    }
    if (select(serv->max_sd + 1, &serv->readfds, NULL, NULL, NULL) < 0) {
        perror("SELECT");
        exit (84);
    }
}

void add_new_socket(serv_t *serv, int new)
{
    if (FD_ISSET(serv->servFd, &serv->readfds)) {
        if ((new = accept(serv->servFd, (struct sockaddr *)&serv->servaddr, \
        (socklen_t *)&serv->len)) < 0) {
            perror("ACCEPT");
            exit (84);
        }
        dprintf(new, "220 Service ready for new user.\r\n");
        for (int i = 0; i < 255; i += 1) {
            if (serv->cli[i].cliFd == 0) {
                serv->cli[i].cliFd = new;
                break;
            }
        }
    }
}

int get_msg(serv_t *serv)
{
    memset(serv->msg, 0, 255);
    int nbbyte = 0;

    for (int i = 0; i < 255; i++) {
        serv->sd = serv->cli[i].cliFd;
        if (FD_ISSET( serv->sd , &serv->readfds)) {
            if ((nbbyte = read( serv->sd , serv->msg, 1024)) == 0) {
                serv->cli[i].cliFd = 0;
                return (0);
            }  else {
                serv->actualIndex = i;
                return (1);
            }
        }
    }
    return (0);
}

void manage_response(serv_t *serv)
{
    if (get_msg(serv) == 1) {
        for (int a = 0; a < 5; a += 1)
            if (serv->features[a](serv) > 0)
                return;
        dprintf(serv->sd, "COMMAND NOT FOUND\r\n");
    }
}

void start_server(char **av)
{
    serv_t serv;
    int new = 0;

    init_server(&serv, av);
    init_fct(&serv);
    while (1) {
        set_socket(&serv);
        add_new_socket(&serv, new);
        manage_response(&serv);
    }
}