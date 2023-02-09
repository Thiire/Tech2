/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_2716
*/

#include "C_2716.hpp"

C_2716::C_2716(const std::string &value)
{
    this->size = 24;
    this->value = std::vector<Pin>(24);
    this->value[0].setType(nts::input);
    this->value[1].setType(nts::input);
    this->value[2].setType(nts::input);
    this->value[3].setType(nts::input);
    this->value[4].setType(nts::input);
    this->value[5].setType(nts::input);
    this->value[6].setType(nts::input);
    this->value[7].setType(nts::input);
    this->value[8].setType(nts::output);
    this->value[9].setType(nts::output);
    this->value[10].setType(nts::output);
    this->value[12].setType(nts::output);
    this->value[13].setType(nts::output);
    this->value[14].setType(nts::output);
    this->value[15].setType(nts::output);
    this->value[16].setType(nts::output);
    this->value[18].setType(nts::input);
    this->value[21].setType(nts::input);
    this->value[22].setType(nts::input);
}

C_2716::~C_2716()
{
}

nts::Tristate C_2716::compute(std::size_t pin)
{
    if (pin < this->size) {
        return (this->value[pin].getState());
    } else {
        return (nts::UNDEFINED);
    }
}


std::string C_2716::getType() const
{
    return "2716";
}
