/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4094
*/

#include "C_4094.hpp"

C_4094::C_4094(const std::string &value)
{
    this->size = 16;
    this->value = std::vector<Pin>(16);
    this->value[1].setType(nts::input);
    this->value[2].setType(nts::clock);
    this->value[8].setType(nts::output);
    this->value[9].setType(nts::output);
    this->value[3].setType(nts::output);
    this->value[4].setType(nts::output);
    this->value[5].setType(nts::output);
    this->value[6].setType(nts::output);
    this->value[10].setType(nts::output);
    this->value[11].setType(nts::output);
    this->value[12].setType(nts::output);
    this->value[13].setType(nts::output);
}

C_4094::~C_4094()
{
}

nts::Tristate C_4094::compute(std::size_t pin)
{
    if (pin < this->size) {
        return (this->value[pin].getState());
    } else {
        return (nts::UNDEFINED);
    }
}

std::string C_4094::getType() const
{
    return "4094";
}
