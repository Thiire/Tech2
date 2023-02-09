/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** init
*/

#include "myftp.h"

int init_new_socket(serv_t serv, int socket)
{
    int len = sizeof(serv.address);

    socket = accept(serv.socket, (struct sockaddr *)&serv.address,
    (socklen_t *)&len);
    if (socket < 0) {
        perror("init_new_socket");
        close(serv.socket);
        exit(84);
    }
    dprintf(socket, "220 Service ready for new user.\r\n");
    return (socket);
}

void init_socket(int fd)
{
    int opt = 1;
    int res = 0;

    res = setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
    if (res < 0) {
        perror("init_socket");
        close(fd);
        exit(84);
    }
}

int create_socket(int fd)
{
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == 0) {
        perror("create_socket");
        close(fd);
        exit(84);
    }
    return (fd);
}

void init_adress(int fd, struct sockaddr_in adrs, int port)
{
    int check = 0;

    adrs.sin_addr.s_addr = INADDR_ANY;
    adrs.sin_port = htons(port);
    adrs.sin_family = AF_INET;
    check = bind(fd, (struct sockaddr *)&adrs, sizeof(adrs));
    if (check < 0) {
        perror("init_adress");
        close(fd);
        exit(84);
    }
}

void init_upcoming_socket(int fd)
{
    int res = 0;

    res = listen(fd, 3);
    if (res < 0) {
        perror("init_upcoming_socket");
        close(fd);
        exit(84);
    }
}
