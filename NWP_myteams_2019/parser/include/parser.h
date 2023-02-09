/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** parser
*/

#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

enum Bracket {
    UNDEFINED = -1,
    USERS,
    IUSERS,
    USER,
    IUSER,
    TEAM,
    ITEAM,
    UUID,
    IUUID,
    NAME,
    INAME,
    DESCRIPTION,
    IDESCRIPTION,
    SUBSCRIBERS,
    ISUBSCRIBERS,
    CHANNEL,
    ICHANNEL,
    THREAD,
    ITHREAD,
    MESSAGE,
    IMESSAGE,
    REPLY,
    IREPLY
};

char *getContent(char *);
enum Bracket getBracket(char *);
char **makeTabTab(size_t);
int addUser(char *, char *);
char **getUsers();
char *getUUIDfromName(char *);
void printUserInformation(char *, int);
enum Bracket whichBracket(char *);

#endif /* !PARSER_H_ */
