/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** help
*/

#include "../include/teams.h"

void help2(int fd)
{
    dprintf(fd, " and its sub directories (enable reception of all events from"
    " a team)\n\t/subscribed ?[“team_uuid”] : list all subscribed teams or "
    "list all users subscribed to a team\n"
    "\t/unsubscribe [“team_uuid”] : unsubscribe from a team\n"
    "\t/use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”] : use "
    "specify a context team/channel/thread\n"
    "\t/create : based on what is being used create the sub resource (see "
    "below)\n\t/list : based on what is being used list all the sub resour"
    "ces (see below)\n\t/info : based on what is being used list the curren"
    "t (see below)\n");
}

int help(serv_t *serv)
{
    if (strncmp(serv->msg + 1, "help", 4) == 0) {
        dprintf(serv->sd, "\t/login [“username”] : set the username used by "
        "client\n\t/logout : disconnect the client from the server\n"
        "\t/users : get the list of all users that exist on the domain\n"
        "\t/user [“user_uuid”] : get information about a user\n"
        "\t/send [“user_uuid”] [“message_body”] : send a message to a user\n"
        "\t/messages [“user_uuid”] : list all messages exchange with an "
        "user\n\t/subscribe [“team_uuid”] : subscribe to the event of a team");
        help2(serv->sd);
        return (1);
    }
    return (-1);
}