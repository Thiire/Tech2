/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** teams
*/

#ifndef TEAMS_H_
#define TEAMS_H_

#include <stdio.h>
#include <stdarg.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <uuid/uuid.h>
#include "../../parser/include/parser.h"
#define DEFAULT_NAME_LENGTH 32
#define DEFAULT_DESCRIPTION_LENGTH 255
#define DEFAULT_BODY_LENGTH 512

typedef struct cli_s
{
    int isLogged;
    char userName[DEFAULT_DESCRIPTION_LENGTH];
    int cliFd;
    char *user_uid;
} cli_t;

typedef struct serv_s
{
    char msg[1024];
    char **users;
    socklen_t len;
    fd_set readfds;
    int servFd;
    int max_sd;
    cli_t cli[255];
    int actualIndex;
    int sd;
    int (*features[5])(struct serv_s *serv);
    struct sockaddr_in servaddr;
} serv_t;

void init_serv2(serv_t *serv);

void init_server(serv_t *serv, char **av);

void init_fct(serv_t *serv);

void start_server(char **av);

int checkUsers(serv_t *serv, char *user);

int login(serv_t *serv);

int logout(serv_t *serv);

char *getArgument(serv_t *serv);

int help(serv_t *);

int users(serv_t *serv);

int user(serv_t *serv);
#endif /* !TEAMS_H_ */
