/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4040
*/

#include "C_4040.hpp"

C_4040::C_4040(const std::string &value)
{
    this->size = 16;
    this->value = std::vector<Pin>(16);
    this->value[9].setType(nts::clock);
    this->value[2].setType(nts::output);
    this->value[13].setType(nts::output);
    this->value[14].setType(nts::output);
    this->value[1].setType(nts::output);
    this->value[3].setType(nts::output);
    this->value[4].setType(nts::output);
    this->value[5].setType(nts::output);
    this->value[6].setType(nts::output);
    this->value[8].setType(nts::output);
    this->value[10].setType(nts::input);
    this->value[11].setType(nts::output);
    this->value[12].setType(nts::output);
}

C_4040::~C_4040()
{
}

nts::Tristate C_4040::compute(std::size_t pin)
{
    if (pin < this->size) {
        return (this->value[pin].getState());
    } else {
        return (nts::UNDEFINED);
    }
}

std::string C_4040::getType() const
{
    return "4040";
}
