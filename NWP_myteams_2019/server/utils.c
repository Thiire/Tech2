/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** utils
*/

#include "include/teams.h"

char *getArgument(serv_t *serv)
{
    int index = 0;
    char *arg = calloc(1024, sizeof(char));

    for (; serv->msg[index] && serv->msg[index] != '"'; index += 1);
    if (serv->msg[index] != '"')
        return (NULL);
    index++;
    for (int a = 0; serv->msg[index] && serv->msg[index] != '"'; \
    a += 1, index += 1)
        arg[a] = serv->msg[index];
    if (serv->msg[index] != '"')
        return (NULL);
    return (arg);
}

int checkUsers(serv_t *serv, char *user)
{
    for (int a = 0; a < 255; a++) {
        if (strcmp(serv->cli[a].userName, user) == 0)
            return (2);
    }
    for (int a = 0; serv->users[a] != NULL; a += 1)
        if (strcmp(serv->users[a], user) == 0)
            return (1);
    return (0);
}