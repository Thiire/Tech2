/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** parser1
*/

#include "./include/parser.h"

char *getContent(char *str)
{
    char *dest = calloc(256, sizeof(char));
    int idx = 0;

    for (; str[0] && (str[0] == ' ' || str[0] == '\t'); str += 1);
    if (str[0] && str[0] == '<') {
        for (; str[0] && str[0] != '>'; str += 1);
        str+= 1;
        for(idx = 0; str[idx] && str[idx] != '<'; idx++);
        strncat(dest, str, idx);
        return (dest);
    }
    return (NULL);
}

enum Bracket getBracket(char *str)
{
    char dest[256] = {0};
    int idx = 0;

    for (; str[0] && (str[0] == ' ' || str[0] == '\t'); str += 1);
    if (str[0] && str[0] == '<') {
        for (idx = 0; str[idx] && str[idx] != '>'; idx++);
        strncat(dest, str, idx + 1);
        return (whichBracket(dest));
    }
    return (-1);
}

void addString(FILE *file, char *str, int nb)
{
    int idx = 0;
    char buffer[10000] = {0};

    fseek(file, nb, SEEK_SET);
    for (idx = 0; (buffer[idx] = fgetc(file)) != EOF; idx++);
    buffer[idx] = 0;
    fseek(file, nb, SEEK_SET);
    fputs(str, file);
    fseek(file, nb + strlen(str), SEEK_SET);
    fputs(buffer, file);
}

int addUser(char *str, char *uuid)
{
    char buffer[256] = {0};
    char res[512] = "\t\t<User>\n\t\t\t<Name>";
    FILE *file = fopen("../data/Data.xml", "r+b");

    strcat(res, str);
    strcat(res, "</Name>\n\t\t\t<UUID>");
    strcat(res, uuid);
    strcat(res, "</UUID>\n\t\t</User>\n");
    while (fgets(buffer, sizeof(buffer), file)) {
        if (getBracket(buffer) == USERS) {
            addString(file, res, ftell(file));
            fclose(file);
            return (1);
        }
    }
    fclose(file);
    return (0);
}

char **getUsers()
{
    FILE *file = fopen("../data/Data.xml", "r");
    char **res = makeTabTab(100);
    char buffer[256] = {0};
    int start = -1;

    while (fgets(buffer, sizeof(buffer), file)) {
        if (getBracket(buffer) == USERS) {
            start = 0;
        } else if (getBracket(buffer) == IUSERS) {
            break;
        } else if (start != -1) {
            if (getBracket(buffer) == NAME) {
                res[start] = getContent(buffer);
                start++;
            }
        }
    }
    res[start] = NULL;
    fclose(file);
    return (res);
}