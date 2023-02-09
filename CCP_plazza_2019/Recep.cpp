/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Recep
*/

#include "Recep.hpp"

void Recep::start()
{
    std::string input;
    char buf[1024] = {0};

    this->addKitchen();
    while (1) {
        this->checkKitchen();
        this->kitchenMessage();
        read(0, buf, 1024);
        input = buf;
        if (input.back() == '\n') {
            input.pop_back();
        }
        if (this->_pipe.checkChild() == 0) {
            break;
        } else if (input.empty()) {
            continue;
        } else if (!input.compare("status")) {
            for (int idx = 0; idx < this->_status.size(); idx++) {
                this->_status[idx] = true;
            }
        } else if (!input.compare("STOP")) {
            break;
        } else {
            try {
                std::string type = input.substr(0, input.find(" "));
                std::string size = input.substr(input.find(" ") + 1, (input.find(" ", input.find(" ") + 1) - input.find(" ") - 1));
                for (size_t idx = 0; idx < std::stoi(input.substr((input.find(" ", input.find(" ") + 1) + 2))); idx++) {
                    this->_list.push(Pizza<std::string, std::string>(type, size));
                }
                for (int i = input.find(';'); i != input.npos; i = input.find(';')) {
                    input = input.substr(i + 2);
                    std::string type = input.substr(0, input.find(" "));
                    std::string size = input.substr(input.find(" ") + 1, (input.find(" ", input.find(" ") + 1) - input.find(" ") - 1));
                    for (size_t idx = 0; idx < std::stoi(input.substr((input.find(" ", input.find(" ") + 1) + 2))); idx++) {
                        this->_list.push(Pizza<std::string, std::string>(type, size));
                    }
                }
            } catch(const std::out_of_range &err) {
                continue;
            } catch (const std::exception &e) {
                std::cerr << "Input User Error => " << e.what() << std::endl;
                exit(84);
            }
        }
        memset(buf, 0, 1024);
    }
}

void Recep::kitchenMessage()
{
    std::string input = "0";
    std::string stock = "";

    for (int idx = 0; idx < this->_pipe.getSize(); idx++, input = std::to_string(idx)) {
        this->_pipe >> input;

        if (!input.empty()) {
            if (input.compare(input.find(" ") + 1, 7, "Kill me") == 0) {
                stock = std::to_string(idx) + " STOP";
                this->_pipe << stock;
                this->_pipe.killChild(std::stoi(input));
            } else if (input.compare(input.find(" ") + 1, 10, "need Pizza") == 0) {
                Pizza<std::string, std::string> tmp(-1, -1);
                if (this->_list.tryPop(tmp)) {
                    stock = std::to_string(idx) + " " + std::to_string(tmp.getType()) + " " + std::to_string(tmp.getSize());
                    this->_pipe << stock;
                } else {
                    stock = std::to_string(idx) + " no Pizza";
                    this->_pipe << stock;
                }
            } else if (input.compare(input.find(" ") + 1, 12, "need State ?") == 0) {
                if (this->_status[std::stoi(input)] == true) {
                    stock = std::to_string(idx) + " yes Need";
                    this->_pipe << stock;
                    this->_status[std::stoi(input)] = false;
                } else {
                    stock = std::to_string(idx) + " no Need";
                    this->_pipe << stock;
                }
            }
        }
    }
}

void Recep::addKitchen()
{
    int pid = 0;

    this->_pipe.addChild();
    pid = fork();
    if (pid == -1)
        exit (84);
    if (pid == 0) {
        Kitchen kitchen(this->_pipe, this->_multi, this->_nb_cook, this->_time);
        kitchen.start();
        exit(0);
    } else
        this->_pipe.closeChild();
        this->_status.push_back(false);
    }

bool Recep::checkKitchen()
{
    if (this->_pipe.checkChild() * this->_nb_cook < this->_list.getSize()) {
        this->addKitchen();
    }
}

int Recep::getNbCook() const
{
    return _nb_cook;
}

Recep::Recep(int multiplier, int cook, int time)
{
    this->_multi = multiplier;
    this->_nb_cook = cook;
    this->_time = time;
}

Recep::~Recep()
{
}
