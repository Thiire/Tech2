/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login
*/

#include "../include/teams.h"

char *create_user_uid()
{
    uuid_t tmpuuid;
    char *uuid = calloc(512, sizeof(char));

    uuid_generate_random(tmpuuid);
    uuid_unparse(tmpuuid, uuid);
    return (uuid);
}

int create_user(serv_t *serv, char *arg, int check)
{
    if (serv->cli[serv->actualIndex].isLogged != 1 && check == 0) {
        dprintf(serv->sd, "%s successfully Created\r\n", arg);
        strcpy(serv->cli[serv->actualIndex].user_uid, create_user_uid());
        serv->cli[serv->actualIndex].isLogged = 1;
        strcpy(serv->cli[serv->actualIndex].userName, arg);
        addUser(arg, serv->cli[serv->actualIndex].user_uid);
        serv->users = getUsers();
        return (1);
    }
    return (0);
}

int log_user(serv_t *serv, char *arg, int check)
{
    if (check == 1 && \
        serv->cli[serv->actualIndex].isLogged != 1) {
        dprintf(serv->sd, "%s successfully Logged\r\n", arg);
        serv->cli[serv->actualIndex].isLogged = 1;
        strcpy(serv->cli[serv->actualIndex].userName, arg);
        if (getUUIDfromName(arg) == NULL) {
            printf("Error Log USER\n");
            exit (84);
        }
        strcpy(serv->cli[serv->actualIndex].user_uid, getUUIDfromName(arg));
        return (1);
    }
    return (0);
}

int login(serv_t *serv)
{
    int check = 0;

    if (strncmp(serv->msg + 1, "login", 5) == 0) {
        char *arg = getArgument(serv);
        if (arg == NULL) {
            dprintf(serv->sd, "Error\r\n");
            return (1);
        }
        check = checkUsers(serv, arg);
        if (check == 2) {
            dprintf(serv->sd, "User Actually logged\r\n");
        } else if (log_user(serv, arg, check) != 1 && \
        create_user(serv, arg, check) != 1)
            dprintf(serv->sd, "Error Login\r\n");
        return (1);
    }
    return (-1);
}

int logout(serv_t *serv)
{
    if (strncmp(serv->msg + 1, "logout", 6) == 0) {
        if (serv->cli[serv->actualIndex].isLogged) {
            serv->cli[serv->actualIndex].isLogged = 0;
            serv->cli[serv->actualIndex].cliFd = 0;
            dprintf(serv->sd, "%s Successfully Disconnected\r\n", \
            serv->cli[serv->actualIndex].userName);
            memset(serv->cli[serv->actualIndex].userName, 0, \
            DEFAULT_NAME_LENGTH);
            close(serv->sd);
        } else {
            serv->cli[serv->actualIndex].cliFd = 0;
            close(serv->sd);
        }
        return (1);
    }
    return (-1);
}