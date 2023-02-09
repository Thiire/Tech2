/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** message
*/

#include "./include/client.h"

void cli_message(int clifd)
{
    char buff[1024] = {0};
    int n;

    while (1) {
        read(clifd, buff, sizeof(buff));
        printf("From Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        write(clifd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
    }
    close(clifd);
}