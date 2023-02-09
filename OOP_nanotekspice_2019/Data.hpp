/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Data
*/

#ifndef DATA_HPP_
#define DATA_HPP_

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Pin.hpp"
#include "Circuit.hpp"
#include "Factory.hpp"

class Circuit;
class Pin;
namespace nts {
    class IComponent;
}

class Data {
    public:
        Data() {};
        ~Data() {this->_pin.clear(); this->_circuit.clear();};
        void parsefile_chipsets(std::string name);
        void parsefile_links(std::string name);
        void parse_input(char **av, int ac);
        void add_pin(std::string, std::string);
        void add_circuit(std::string, std::string);
        std::shared_ptr<nts::IComponent> getComponent(std::string str);
        void change_input(std::string);
        void print_output();
        void print_all();
        void simulate();

        Factory factory;
        static bool prompt;

    protected:
    private:
        std::vector<std::shared_ptr<nts::IComponent>> _pin;
        std::vector<std::shared_ptr<nts::IComponent>> _circuit;
        std::vector<std::string> _namepin;
        std::vector<std::string> _namecir;
};

#endif /* !DATA_HPP_ */
