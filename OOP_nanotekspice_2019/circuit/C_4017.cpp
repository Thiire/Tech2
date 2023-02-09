/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4017
*/

#include "C_4017.hpp"

C_4017::C_4017(const std::string &value)
{
    this->size = 15;
    this->value = std::vector<Pin>(15);
    this->value[0].setType(nts::output);
    this->value[1].setType(nts::output);
    this->value[2].setType(nts::output);
    this->value[3].setType(nts::output);
    this->value[4].setType(nts::output);
    this->value[5].setType(nts::output);
    this->value[6].setType(nts::output);
    this->value[8].setType(nts::output);
    this->value[9].setType(nts::output);
    this->value[10].setType(nts::output);
    this->value[11].setType(nts::output);
    this->value[12].setType(nts::clock);
    this->value[13].setType(nts::input);
}

C_4017::~C_4017()
{
}

nts::Tristate C_4017::compute(std::size_t pin)
{
    if (pin < this->size) {
        return (this->value[pin].getState());
    } else {
        return (nts::UNDEFINED);
    } 
}

std::string C_4017::getType() const
{
    return "4017";
}
