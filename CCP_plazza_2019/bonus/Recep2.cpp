/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Recep
*/

#include "Recep2.hpp"

void Recep::start()
{       
        this->checkKitchen();
        this->kitchenMessage();
        if (this->_pipe.checkChild() == 0) {
            return;
        } else if (_input.empty()) {
            return;
        } else if (!_input.compare("STOP")) {
            return;
        } else {
            try {
                std::string type = _input.substr(0, _input.find(" "));
                std::string size = _input.substr(_input.find(" ") + 1, (_input.find(" ", _input.find(" ") + 1) - _input.find(" ") - 1));
                for (size_t idx = 0; idx < std::stoi(_input.substr((_input.find(" ", _input.find(" ") + 1) + 2))); idx++) {
                    this->_list.push(Pizza<std::string, std::string>(type, size));
                }
                for (int i = _input.find(';'); i != _input.npos; i = _input.find(';')) {
                    _input = _input.substr(i + 2);
                    std::string type = _input.substr(0, _input.find(" "));
                    std::string size = _input.substr(_input.find(" ") + 1, (_input.find(" ", _input.find(" ") + 1) - _input.find(" ") - 1));
                    for (size_t idx = 0; idx < std::stoi(_input.substr((_input.find(" ", _input.find(" ") + 1) + 2))); idx++) {
                        this->_list.push(Pizza<std::string, std::string>(type, size));
                    }
                }
            } catch(const std::out_of_range &err) {
                return;
            } catch (const std::exception &e) {
                std::cerr << "Input User Error => " << e.what() << std::endl;
                exit(84);
            }
            _input.clear();
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
                    for (int a = 0; a < _nb_cook; a += 1) {
                        if (_kitchens[std::stoi(input)][a]->isAvailable()) {
                            Pizza<std::string, std::string> tmp2(tmp.getType(), tmp.getSize());
                            _kitchens[std::stoi(input)][a]->makePizza(tmp2);
                            break;
                        }
                    }
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

int Recep::getNbKitchen()
{
    return _pipe.checkChild();
}

Pipe Recep::getPipe() const
{
    return _pipe;
}

std::vector<std::vector<Cook *>> &Recep::getKitchens()
{
    return this->_kitchens;
}

void Recep::addKitchen()
{
    int pid = 0;

    std::vector<Cook *> tmp;
    for (int b = 0; b < _nb_cook; b += 1) {
        tmp.push_back(new Cook(this->_multi, this->_time, this->_pipe.getSize(), b));
    }
    _kitchens.push_back(tmp);
    this->_pipe.addChild();
    pid = fork();
    if (pid == -1)
        exit (84);
    if (pid == 0) {
        Kitchen kitchen(this->_pipe, this->_multi, this->_nb_cook, this->_time);
        kitchen.start();
        exit(0);
    } else {
        this->_pipe.closeChild();
        this->_status.push_back(false);
    }
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

void Recep::setInput(std::string &str)
{
    _input = str;
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
