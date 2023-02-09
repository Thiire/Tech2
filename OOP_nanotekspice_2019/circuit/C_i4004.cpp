/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_i4004
*/

#include "C_i4004.hpp"

C_i4004::C_i4004(const std::string &value)
{
    this->size = 16;
    this->value = std::vector<Pin>(16);
    this->value[0].setType(nts::input);
    this->value[1].setType(nts::input);
    this->value[2].setType(nts::input);
    this->value[3].setType(nts::input);
    this->value[5].setType(nts::clock);
    this->value[6].setType(nts::clock);
    this->value[12].setType(nts::output);
    this->value[13].setType(nts::output);
    this->value[14].setType(nts::output);
    this->value[15].setType(nts::output);
}

C_i4004::~C_i4004()
{
}

nts::Tristate C_i4004::compute(std::size_t pin)
{
    if (pin < this->size) {
        return (this->value[pin].getState());
    } else {
        return (nts::UNDEFINED);
    }
}

std::string C_i4004::getType() const
{
    return "i4004";
}