/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Data
*/

#include "Data.hpp"

void Data::change_input(std::string str)
{
    std::string input = str.substr(0, str.find("="));
    std::string value = str.substr(str.find("=") + 1);
    if (std::stoi(value) == -1) {
        if (this->getComponent(input)->getType() == "input") {
            this->getComponent(input)->setState(nts::UNDEFINED);
        } else {
            std::cerr << "You can only set an input" << std::endl;
            exit (84);
        }
    } else if (std::stoi(value) == 0) {
        if (this->getComponent(input)->getType() == "input") {
            this->getComponent(input)->setState(nts::FALSE);
        } else {
            std::cerr << "You can only set an input" << std::endl;
            exit (84);
        }
    } else if (std::stoi(value) == 1) {
        if (this->getComponent(input)->getType() == "input") {
            this->getComponent(input)->setState(nts::TRUE);
        } else {
            std::cerr << "You can only set an input" << std::endl;
            exit (84);
        }
    } else {
        std::cerr << "this value [" << value << "] is unknow" << std::endl;
        exit(84);
    }
}

void Data::print_output()
{
    for (size_t i = 0; i < this->_namepin.size(); i++) {
        if (this->_pin[i]->getType() == "output") {
            if (this->_pin[i]->getState() == nts::UNDEFINED) {
                std::cout << this->_namepin[i] << "=U" << std::endl;
            } else {
                std::cout << this->_namepin[i] << "=" << this->_pin[i]->getState() << std::endl;
            }
        }
    }
}

void Data::add_pin(std::string to_add, std::string type)
{
    std::vector<std::string>::iterator it;
    std::vector<std::string>::iterator it2;
    std::shared_ptr<nts::IComponent> ret(std::make_unique<Pin>(type));
    

    for (it = this->_namepin.begin(); !this->_namepin.empty() && it != this->_namepin.end(); it++) {
        if (!it->compare(to_add)) {
            std::cerr << "[" << to_add << "]" << " Already exist" << std::endl;
            exit(84);
        }
    }
    for (it2 = this->_namecir.begin(); !this->_namecir.empty() && it2 != this->_namecir.end(); it2++) {
        if (!it2->compare(to_add)) {
            std::cerr << "[" << to_add << "]" << " Already exist" << std::endl;
            exit(84);
        }
    }
    this->_namepin.push_back(to_add);
    this->_pin.push_back(ret);
}

void Data::add_circuit(std::string to_add, std::string type)
{
    std::vector<std::string>::iterator it;
    std::vector<std::string>::iterator it2;

    for (it = this->_namepin.begin(); !this->_namepin.empty() && it != this->_namepin.end(); it++) {
        if (!it->compare(to_add)) {
            std::cerr << "[" << to_add << "]" << " Already exist" << std::endl;
            exit(84);
        }
    }
    for (it2 = this->_namecir.begin(); !this->_namecir.empty() && it2 != this->_namecir.end(); it2++) {
        if (!it2->compare(to_add)) {
            std::cerr << "[" << to_add << "]" << " Already exist" << std::endl;
            exit(84);
        }
    }
    this->_namecir.push_back(to_add);
    this->_circuit.push_back(factory.createComponent(type, to_add));
}

void Data::print_all()
{
    std::vector<Pin>::iterator it1;
    std::vector<std::unique_ptr<nts::IComponent>>::iterator it2;
    std::vector<std::string>::iterator it3;
    std::vector<std::string>::iterator it4;

    for (size_t i = 0; i < this->_namepin.size(); i++) {
        std::cout << this->_pin[i]->getType() << " " << this->_namepin[i] << " = " << this->_pin[i]->getState() << std::endl;
    }
    std::cout << std::endl;
    for (size_t i = 0; i < this->_namecir.size(); i++) {
        std::cout << this->_circuit[i]->getType() << " " << this->_namecir[i] << ": {" << std::endl;
        this->_circuit[i]->dump();
        std::cout << "}" << std::endl;
    }
}

void Data::parsefile_chipsets(std::string name)
{
    std::ifstream file;
    std::string data;
    bool check = false;

    file.open(name);
    if (file.is_open()) {
        while (std::getline(file, data) && data.find(".links:")) {
            while (data.find("\t") != data.npos) {
                data.replace(data.find("\t"), 1, 1, ' ');
            }
            while (data.find("  ") != data.npos) {
                data.replace(data.find("  "), 2, 1, ' ');
            }
            if (data.find_first_of(" ") == 0) {
                data.erase(0, 1);
            }
            if (!data.find("#") || data.size() == 0) {
                continue;
            }
            if (!data.find(".chipsets:")) {
                check = true;
                continue;
            }
            if (!data.find("input")) {
                this->add_pin(data.substr(6), "input");
            } else if (!data.find("output")) {
                this->add_pin(data.substr(7), "output");
            } else if (!data.find("clock")) {
                this->add_pin(data.substr(6), "clock");
            } else if (!data.find("true")) {
                this->add_pin(data.substr(5), "true");
            } else if (!data.find("false")) {
                this->add_pin(data.substr(6), "false");
            } else if (data.size() > 0) {
                this->add_circuit(data.substr(data.find(" ") + 1), data.substr(0, data.find(" ")));
            }
        }
        if (check == false) {
            std::cerr << "No .chipsets section" << std::endl;
            exit (84);
        }
    } else {
        std::cerr << "Bad files" << std::endl;
        exit (84);
    }
    file.close();
}

void Data::parsefile_links(std::string name)
{
    std::ifstream file;
    std::string data;
    std::string input1;
    std::string input2;
    std::string input1a;
    std::string input1b;
    std::string input2a;
    std::string input2b;

    file.open(name);
    if (file.is_open()) {
        while (std::getline(file, data) && data.find(".links:"));
        if (data.compare(".links:")) {
            std::cerr << "No .links sections" << std::endl;
            exit(84);
        }
        while (std::getline(file, data)) {
            while (data.find("\t") != data.npos) {
                data.replace(data.find("\t"), 1, 1, ' ');
            }
            while (data.find("  ") != data.npos) {
                data.replace(data.find("  "), 2, 1, ' ');
            }
            if (!data.find("#")) {
                continue;
            }
            if (data.find(" ") < data.size()) {
                input1 = data.substr(0, data.find(" "));
                input2 = data.substr(data.find(" ") + 1);
                if (input1.find(":") < input1.size()) {
                    input1a = input1.substr(0, input1.find(":"));
                    input1b = input1.substr(input1.find(":") + 1);
                } else {
                    std::cerr << "Bad files" << std::endl;
                    exit (84);
                }
                if (input2.find(":") < input2.size()) {
                    input2a = input2.substr(0, input2.find(":"));
                    input2b = input2.substr(input2.find(":") + 1);
                } else {
                    std::cerr << "Bad files" << std::endl;
                    exit (84);
                }
                this->getComponent(input2a)->setLink(std::stoi(input2b), *this->getComponent(input1a), std::stoi(input1b));
            }
        }
    } else {
        std::cerr << "Bad files" << std::endl;
        exit (84);
    }
    file.close();
}

void Data::parse_input(char **av, int ac)
{
    std::string input;
    std::string value;
    std::string str;
    
    if (av[2] == NULL) {
        return;
    }
    for (int i = 2; i < ac; i++) {
        str = av[i];
        if (str.find("=") < str.size()) {
            input = str.substr(0, str.find("="));
            value = str.substr(str.find("=") + 1);
            if (std::stoi(value) == -1) {
                this->getComponent(input)->setState(nts::UNDEFINED);
            } else if (std::stoi(value) == 0) {
                this->getComponent(input)->setState(nts::FALSE);
            } else if (std::stoi(value) == 1) {
                this->getComponent(input)->setState(nts::TRUE);
            } else {
                std::cerr << "this value [" << value << "] is unknow" << std::endl;
                exit(84);
            }
        } else {
            std::cerr << "Bad input" << std::endl;
            exit (84);
        }
    }
}

std::shared_ptr<nts::IComponent> Data::getComponent(std::string str)
{

    for (size_t i = 0; i < this->_namecir.size(); i++) {
        if (str == this->_namecir[i]) {
            return this->_circuit[i];
        }
    }
    for (size_t i = 0; i < this->_namepin.size(); i++) {
        if (str == this->_namepin[i]) {
            return this->_pin[i];
        }
    }
    std::cerr << "this component [" << str << "] doesn't exist" << std::endl;
    exit(84);
}


void Data::simulate()
{
    for (size_t i = 0; i < this->_namecir.size(); i++) {
        this->_circuit[i]->compute(1);
    }
}
