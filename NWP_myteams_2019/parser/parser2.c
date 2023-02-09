/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** parser1
*/

#include "./include/parser.h"

int getType(char *buffer, int type, char **stock, char**address)
{
    int res = -1;
    if (getBracket(buffer) == TEAM) {
        res = 0;
    } else if (getBracket(buffer) == CHANNEL) {
        res = 1;
    } else if (getBracket(buffer) == THREAD) {
        res = 2;
    } else if (getBracket(buffer) == REPLY) {
        res = -1;
    } else {
        return (type);
    }
    *stock = NULL;
    *address = NULL;
    return (res);
}

void writeMessage(int fd, int type, char *stock, char *address)
{
    if (stock == NULL) {
        return;
    }
    switch (type) {
        case 0:
            dprintf(fd, "\tIs in '%s' team, UUID: '%s'\n", stock, address);
            break;
        case 1:
            dprintf(fd, "\t- Own '%s' channel, UUID: '%s'\n", stock, address);
            break;
        case 2:
            dprintf(fd, "\t-- Has '%s' thread, UUID: '%s'\n", stock, address);
            break;
        case 3:
            dprintf(fd, "\t--- Writed '%s' message\n", stock);
            break;
        default:
            break;
    }
}

void printUserInformation(char *name, int fd)
{
    FILE *file = fopen("../data/Data.xml", "r");
    char buffer[256] = {0};
    int type = -1;
    char *stock = NULL;
    char *address = NULL;

    while (fgets(buffer, sizeof(buffer), file)) {
        type = getType(buffer, type, &stock, &address);
        if (getBracket(buffer) == NAME && type != -1 && stock == NULL) {
            stock = getContent(buffer);
        } else if (getBracket(buffer) == UUID &&
        strcmp(getContent(buffer), name) && address == NULL && type != -1) {
            address = getContent(buffer);
        } else if (getBracket(buffer) == UUID &&
        !strcmp(getContent(buffer), name) && type != -1) {
            writeMessage(fd, type, stock, address);
            stock = NULL;
            address = NULL;
            type = -1;
        }
    }
    fclose(file);
}

char *getUUIDfromName(char *name)
{
    FILE *file = fopen("../data/Data.xml", "r");
    char buffer[256] = {0};
    int start = -1;

    while (fgets(buffer, sizeof(buffer), file)) {
        if (getBracket(buffer) == USERS) {
            start = 0;
        } else if (getBracket(buffer) == IUSERS) {
            break;
        } else if (start != -1) {
            if (getBracket(buffer) == NAME &&
            !strcmp(getContent(buffer), name)) {
                fgets(buffer, sizeof(buffer), file);
                if (getBracket(buffer) == UUID)
                    return (getContent(buffer));
            }
        }
    }
    fclose(file);
    return (NULL);
}
