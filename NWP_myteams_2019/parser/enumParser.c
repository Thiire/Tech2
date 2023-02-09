/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** enumParser
*/


#include "./include/parser.h"

char **makeTabTab(size_t size)
{
    char **res = malloc(sizeof(char *) * size);

    for (size_t idx = 0; idx < size; idx += 1) {
        res[idx] = calloc(256, sizeof(char));
    }
    return (res);
}

enum Bracket whichBracket3(char *str)
{
    if (!strcmp(str, "</Message>")) {
        return (IMESSAGE);
    } else if (!strcmp(str, "<Reply>")) {
        return (REPLY);
    } else if (!strcmp(str, "</Reply>")) {
        return (IREPLY);
    } else if (!strcmp(str, "</Name>")) {
        return (INAME);
    }
    return (UNDEFINED);
}

enum Bracket whichBracket2(char *str)
{
    if (!strcmp(str, "<Description>")) {
        return (DESCRIPTION);
    } else if (!strcmp(str, "</Description>")) {
        return (IDESCRIPTION);
    } else if (!strcmp(str, "<Subscribers>")) {
        return (SUBSCRIBERS);
    } else if (!strcmp(str, "</Subscribers>")) {
        return (ISUBSCRIBERS);
    } else if (!strcmp(str, "<Channel>")) {
        return (CHANNEL);
    } else if (!strcmp(str, "</Channel>")) {
        return (ICHANNEL);
    } else if (!strcmp(str, "<Thread>")) {
        return (THREAD);
    } else if (!strcmp(str, "</Thread>")) {
        return (ITHREAD);
    } else if (!strcmp(str, "<Message>")) {
        return (MESSAGE);
    }
    return (whichBracket3(str));
}

enum Bracket whichBracket(char *str)
{
    if (!strcmp(str, "<Users>")) {
        return (USERS);
    } else if (!strcmp(str, "</Users>")) {
        return (IUSERS);
    } else if (!strcmp(str, "<User>")) {
        return (USER);
    } else if (!strcmp(str, "</User>")) {
        return (IUSER);
    } else if (!strcmp(str, "<Team>")) {
        return (TEAM);
    } else if (!strcmp(str, "</Team>")) {
        return (ITEAM);
    } else if (!strcmp(str, "<UUID>")) {
        return (UUID);
    } else if (!strcmp(str, "</UUID>")) {
        return (IUUID);
    } else if (!strcmp(str, "<Name>")) {
        return (NAME);
    }
    return (whichBracket2(str));
}