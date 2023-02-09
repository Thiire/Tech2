/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client
*/

#include "./include/client.h"

void assign_ip_port(int port, char *ip, struct sockaddr_in *servaddr)
{
    servaddr->sin_family = AF_INET;
    servaddr->sin_addr.s_addr = inet_addr(ip);
    servaddr->sin_port = htons(port);
}

int create_socket(struct sockaddr_in *servaddr)
{
    int clifd = socket(AF_INET, SOCK_STREAM, 0);
    if (clifd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    } else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
    return (clifd);
}

void start_client(int port, char *ip)
{
    int clifd = 0;
    struct sockaddr_in servaddr;

    clifd = create_socket(&servaddr);
    assign_ip_port(port, ip, &servaddr);
    if (connect(clifd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    } else
        printf("connected to the server..\n");
    cli_message(clifd);
}