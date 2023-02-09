/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4081
*/

#include "C_4081.hpp"

C_4081::C_4081(const std::string &value)
{
    this->size = 14;
    this->value = std::vector<Pin>(14);
    this->value[0].setType(nts::input);
    this->value[1].setType(nts::input);
    this->value[2].setType(nts::output);
    this->value[3].setType(nts::output);
    this->value[4].setType(nts::input);
    this->value[5].setType(nts::input);
    this->value[7].setType(nts::input);
    this->value[8].setType(nts::input);
    this->value[9].setType(nts::output);
    this->value[10].setType(nts::output);
    this->value[11].setType(nts::input);
    this->value[12].setType(nts::input);
}

C_4081::~C_4081()
{
}

nts::Tristate C_4081::compute(std::size_t pin)
{
    this->value[2].setState(AND(this->value[0].getState(), this->value[1].getState()));
    this->value[3].setState(AND(this->value[4].getState(), this->value[5].getState()));
    this->value[9].setState(AND(this->value[7].getState(), this->value[8].getState()));
    this->value[10].setState(AND(this->value[11].getState(), this->value[12].getState()));
    if (pin < this->size) {
        return (this->value[pin].getState());
    } else {
        return (nts::UNDEFINED);
    }
}

std::string C_4081::getType() const
{
    return "4081";
}
