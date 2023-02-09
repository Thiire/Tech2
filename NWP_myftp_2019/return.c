/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** message
*/

#include "myftp.h"

int return_manager5(int s, char *str, int check)
{
    if (strncmp(str, "LIST ", 5) == 0) {
        check++;
        dprintf(s, "150 File status okay; about to open data connection.\r\n");
    }
    if (strncmp(str, "PORT ", 5) == 0) {
        check++;
        dprintf(s, "200 Command okay.\r\n");
    }
    if (strncmp(str, "NOOP", 4) == 0) {
        check++;
        dprintf(s, "200 Command okay.\r\n");
    }
    if (check == 2) {
        dprintf(s, "502 Command in progress\r\n");
    }
    check = 2;
    return (check);
}

int return_manager4(int s, char *str, int check)
{
    char tmp[100] = {0};

    if (strncmp(str, "CWD ", 4) == 0) {
        check++;
        if (chdir(strncpy(tmp, str + 4, strlen(str + 4) - 1)) == -1)
            dprintf(s, "550 Unreachable File.\r\n");
        else
            dprintf(s, "250 Requested file action okay, completed.\r\n");
    }
    if (strncmp(str, "DELE ", 5) == 0) {
        check++;
        if (remove(strncpy(tmp, str + 5, strlen(str + 5) - 1)) == 0)
            dprintf(s, "250 Requested file action okay, completed.\r\n");
        else
            dprintf(s, "550 Unreachable File.\r\n");
    }
    return (return_manager5(s, str, check));
}

int return_manager3(int s, char *str, int check)
{
    char cwd[50];

    if (strncmp(str, "PWD", 3) == 0) {
        check++;
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            dprintf(s, "%s", my_strcat(my_strcat("257 \"", cwd),
            "\" created\r\n"));
        } else {
            dprintf(s, "xxx Error (RFC compliant)\r\n");
        }
    }
    if (strncmp(str, "PASV", 4) == 0) {
        check++;
        dprintf(s, "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2)\r\n");
    }
    if (strncmp(str, "HELP ", 5) == 0) {
        check++;
        dprintf(s, "214 It's a FTP server nothing more.\r\n");
    }
    return (return_manager4(s, str, check));
}

int return_manager2(int s, char *str, int check)
{
    if (strncmp(str, "QUIT", 4) == 0) {
        dprintf(s, "221 Service closing control connection.\nLogged out"
                " if appropriate.\r\n");
        close(s);
        return (check);
    }
    if (check != 2) {
        dprintf(s, "530 Can't logged in.\r\n");
        return (check);
    }
    if (strncmp(str, "CDUP", 4) == 0) {
        check++;
        if (chdir("../") == -1)
            dprintf(s, "550 Unreachable File.\r\n");
        else
            dprintf(s, "250 Requested file action okay, completed.\r\n");
    }
    return (return_manager3(s, str, check));
}

int return_manager(int s, char *b, int check)
{
    if (strncmp(b, "USER ", 5) == 0) {
        if ((strncmp(b + 5, "Anonymous\r\n", strlen(b + 5)) == 0 &&
        check == 0) || (strncmp(b + 5, "Anonymous\n", strlen(b + 5))) == 0) {
            check++;
            dprintf(s, "331 User name okay, need password.\r\n");
        } else if (check == 0) {
            check++;
            dprintf(s, "331 User name okay, need password.\r\n");
        } else
            dprintf(s, "530 Unable to logged in.\r\n");
        return (check);
    }
    if (strncmp(b, "PASS ", 5) == 0) {
        if ((strlen(b) == 5 && check == 1) || (strlen(b) == 6 && check == 1) ||
        (strlen(b) == 7 && check == 1)) {
            check++;
            dprintf(s, "230 User logged in, proceed.\r\n");
        } else
            dprintf(s, "530 Unable to logged in.\r\n");
        return (check);
    }
    return (return_manager2(s, b, check));
}