/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** myftp
*/

#ifndef MYFTP_H_
#define MYFTP_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>
#include <sys/time.h>
#include <signal.h>
#include <ctype.h>

typedef struct serv_s
{
    int socket;
    int max_sd;
    struct sockaddr_in address;
} serv_t;

int create_socket(int);
void init_socket(int);
int init_new_socket(serv_t , int);
void init_upcoming_socket(int);
void init_adress(int, struct sockaddr_in, int);
int setup_server(serv_t , int);
int message_handler(int *, fd_set, int *);
int return_manager(int, char *, int);
int return_manager2(int, char *, int);
void loop(serv_t, int *, int *, int);
char *my_strcat(char *, char *);

#endif /* !MYFTP_H_ */
