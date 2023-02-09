/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** users
*/

#include "../include/teams.h"

int users(serv_t *serv)
{
    if (strncmp(serv->msg + 1, "users", 5) == 0) {
        dprintf(serv->sd, "List of users:\n");
        for (int idx = 0; serv->users[idx] != NULL; idx++) {
            dprintf(serv->sd, "\t%s\n", serv->users[idx]);
        }
        return (1);
    }
    return (-1);
}

int user(serv_t *serv)
{
    if (strncmp(serv->msg + 1, "user ", 5) == 0) {
        return (1);

    }
    return (-1);
}