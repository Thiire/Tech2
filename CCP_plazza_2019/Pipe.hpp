/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pipe
*/

#ifndef PIPE_HPP_
#define PIPE_HPP_

#include <vector>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

struct fd {
    int child[2];
    int parent[2];
};

class Pipe {
    public:
        Pipe();
        ~Pipe();
        void addChild();
        void KillAll();
        void killChild(int index);
        void closeChild();
        void closeParent();
        void WriteMessage(int index, std::string message);
        std::string ReadMessage(int index);
        int getChild() const;
        int checkChild();
        int getSize();

    protected:
    private:
        std::vector<fd> _fd;

};

void operator<<(Pipe &pipe, std::string arg);
void operator>>(Pipe &pipe, std::string &arg);

#endif /* !PIPE_HPP_ */
