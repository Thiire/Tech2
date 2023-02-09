/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4503
*/

#include "C_4503.hpp"

C_4503::C_4503(const std::string &value)
{
    this->size = 16;
    this->value = std::vector<Pin>(16);
    this->value[1].setType(nts::input);
    this->value[2].setType(nts::output);
    this->value[3].setType(nts::input);
    this->value[4].setType(nts::output);
    this->value[5].setType(nts::input);
    this->value[6].setType(nts::output);
    this->value[8].setType(nts::output);
    this->value[9].setType(nts::input);
    this->value[10].setType(nts::output);
    this->value[11].setType(nts::input);
    this->value[12].setType(nts::output);
    this->value[13].setType(nts::input);
    this->value[14].setType(nts::input);
    this->value[0].setType(nts::input);
}

C_4503::~C_4503()
{
}

nts::Tristate C_4503::compute(std::size_t pin)
{
    if (this->value[0].getState()) {
        this->value[2].setState(nts::UNDEFINED);
        this->value[4].setState(nts::UNDEFINED);
        this->value[6].setState(nts::UNDEFINED);
        this->value[8].setState(nts::UNDEFINED);
    } else {
        this->value[2].setState(OR(this->value[0].getState(), this->value[1].getState()));
        this->value[4].setState(OR(this->value[0].getState(), this->value[3].getState()));
        this->value[6].setState(OR(this->value[0].getState(), this->value[5].getState()));
        this->value[8].setState(OR(this->value[0].getState(), this->value[9].getState()));
    }
    if (this->value[14].getState()) {
        this->value[12].setState(nts::UNDEFINED);
        this->value[10].setState(nts::UNDEFINED);
    } else {
        this->value[12].setState(OR(this->value[14].getState(), this->value[13].getState()));
        this->value[10].setState(OR(this->value[14].getState(), this->value[11].getState()));
    }
    if (pin < this->size) {
        return (this->value[pin].getState());
    } else {
        return (nts::UNDEFINED);
    }
}

std::string C_4503::getType() const
{
    return "4503";
}
