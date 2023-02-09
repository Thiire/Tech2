/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** server
*/

#include "myftp.h"

int setup_server(serv_t serv, int port)
{
    serv.socket = create_socket(serv.socket);
    init_socket(serv.socket);
    init_adress(serv.socket, serv.address, port);
    init_upcoming_socket(serv.socket);
    return (serv.socket);
}

int message_handler(int *_socket, fd_set readfd, int *c_stock)
{
    int val = 0;
    int idx = 0;
    char *str = malloc(sizeof(char) * 1024);

    for (; idx < 100; idx++){
        if (_socket[idx] != 0) {
            if (FD_ISSET(_socket[idx], &readfd)) {
                memset(str, 0, 1024);
                val = read(_socket[idx], str, 1024);
                if (val <= 2) {
                    _socket[idx] = 0;
                    c_stock[idx] = 0;
                } else {
                    c_stock[idx] = return_manager(_socket[idx],
                    str, c_stock[idx]);
                }
            }
        }
    }
    return (c_stock[idx]);
}

int *setup_tab_socket(int *c_socket, int socket)
{
    for (int i = 0; i < 100; i++) {
        if (c_socket[i] != 0)
            continue;
        c_socket[i] = socket;
        break;
    }
    return (c_socket);
}

void loop(serv_t server, int *c_socket, int *c_stock, int socket)
{
    fd_set readfd;
    int i = 0;

    while (1) {
        FD_ZERO(&readfd);
        FD_SET(server.socket, &readfd);
        for (int i = 0; i < 100; i++) {
            if (c_socket[i] > 0)
                FD_SET(c_socket[i], &readfd);
            if (c_socket[i] > server.max_sd)
                server.max_sd = c_socket[i];
        }
        select(100, &readfd, NULL, NULL, NULL);
        if (FD_ISSET(server.socket, &readfd)) {
            socket = init_new_socket(server, socket);
            c_socket = setup_tab_socket(c_socket, socket);
        }
        for (; c_stock[i] != socket && i < 100; i++);
        c_stock[i] = message_handler(c_socket, readfd, c_stock);
    }
}