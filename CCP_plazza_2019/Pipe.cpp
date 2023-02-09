/* 
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pipe
*/

#include "Pipe.hpp"

void operator<<(Pipe &pipe, std::string arg)
{
    pipe.WriteMessage(std::stoi(arg), arg);
}

void operator>>(Pipe &pipe, std::string &arg)
{
    arg = pipe.ReadMessage(std::stoi(arg));
}

int fd_is_valid(int fd) {
    return fcntl(fd, F_GETFD) != -1;
}

Pipe::Pipe()
{
}

Pipe::~Pipe()
{
    for (int idx = 0; idx < this->_fd.size(); idx++) {
        if (fd_is_valid(this->_fd[idx].child[0])) {
            close(this->_fd[idx].child[0]);
        }
        if (fd_is_valid(this->_fd[idx].child[1])) {
            close(this->_fd[idx].child[1]);
        }
        if (fd_is_valid(this->_fd[idx].parent[0])) {
            close(this->_fd[idx].parent[0]);
        }
        if (fd_is_valid(this->_fd[idx].parent[1])) {
            close(this->_fd[idx].parent[1]);
        }
    }
}

void Pipe::KillAll()
{
    for (int idx = 0; idx < this->_fd.size(); idx++) {
        if (fd_is_valid(this->_fd[idx].child[0])) {
            close(this->_fd[idx].child[0]);
        }
        if (fd_is_valid(this->_fd[idx].child[1])) {
            close(this->_fd[idx].child[1]);
        }
        if (fd_is_valid(this->_fd[idx].parent[0])) {
            close(this->_fd[idx].parent[0]);
        }
        if (fd_is_valid(this->_fd[idx].parent[1])) {
            close(this->_fd[idx].parent[1]);
        }
    }
}

void Pipe::closeChild()
{
    close(this->_fd.back().child[0]);
    close(this->_fd.back().parent[1]);
}

void Pipe::closeParent()
{
    close(this->_fd.back().parent[0]);
    close(this->_fd.back().child[1]);
}

int Pipe::checkChild()
{
    int res = 0;

    for (int idx = 0; idx < this->_fd.size(); idx++) {
        if (fd_is_valid(this->_fd[idx].child[0]) || fd_is_valid(this->_fd[idx].child[1]) || fd_is_valid(this->_fd[idx].parent[0]) || fd_is_valid(this->_fd[idx].parent[1])) {
            res++;
        }
    }
    return res;
}

void Pipe::addChild()
{
    fd new_fd;

    if (pipe(new_fd.child) == -1) {
        std::cerr << "Pipe child [" << this->_fd.size() << "] Failed" << std::endl;
        exit (84);
    }
    if (pipe(new_fd.parent) == -1) {
        std::cerr << "Pipe parent [" << this->_fd.size() << "] Failed" << std::endl;
        exit (84);
    }
    fcntl(new_fd.parent[0], F_SETFL, O_NONBLOCK);
    this->_fd.push_back(new_fd);
}

void Pipe::killChild(int index)
{
    if (fd_is_valid(this->_fd[index].child[0])) {
        close(this->_fd[index].child[0]);
    }
    if (fd_is_valid(this->_fd[index].child[1])) {
        close(this->_fd[index].child[1]);
    }
    if (fd_is_valid(this->_fd[index].parent[0])) {
        close(this->_fd[index].parent[0]);
    }
    if (fd_is_valid(this->_fd[index].parent[1])) {
        close(this->_fd[index].parent[1]);
    }
}

void Pipe::WriteMessage(int index, std::string str)
{
    if (fd_is_valid(this->_fd[index].child[1])) {
        dprintf(this->_fd[index].child[1], "%s", str.c_str());
    } else if (fd_is_valid(this->_fd[index].parent[1])) {
        dprintf(this->_fd[index].parent[1], "%s", str.c_str());
    } else {
        std::cout << "not writable" << std::endl;
    }
}

std::string Pipe::ReadMessage(int index)
{
    char str[1024] = {0};
    std::string tmp;

    if (fd_is_valid(this->_fd[index].child[0])) {
        if (read(this->_fd[index].child[0], str, 1024) == 0) {
            exit(84);
        }
        tmp = str;
    } else if (fd_is_valid(this->_fd[index].parent[0])) {
        if (read(this->_fd[index].parent[0], str, 1024) == 0) {
            exit(84);
        }
        tmp = str;
    }
    return tmp;
}

int Pipe::getChild() const
{
    return this->_fd.size() - 1;
}

int Pipe::getSize()
{
    return this->_fd.size(); 
}
