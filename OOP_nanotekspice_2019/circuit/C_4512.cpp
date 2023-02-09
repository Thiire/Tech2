/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4512
*/

#include "C_4512.hpp"

C_4512::C_4512(const std::string &value)
{
    this->size = 16;
    this->value = std::vector<Pin>(16);
    this->value[0].setType(nts::input);
    this->value[1].setType(nts::input);
    this->value[2].setType(nts::input);
    this->value[3].setType(nts::input);
    this->value[4].setType(nts::input);
    this->value[5].setType(nts::input);
    this->value[6].setType(nts::input);
    this->value[8].setType(nts::input);
    this->value[12].setType(nts::input);
    this->value[11].setType(nts::input);
    this->value[10].setType(nts::input);
    this->value[14].setType(nts::input);
    this->value[9].setType(nts::input);
    this->value[13].setType(nts::output);
}

C_4512::~C_4512()
{
}

nts::Tristate C_4512::compute(std::size_t pin)
{
    if (this->value[14].getState() != nts::FALSE) {
        this->value[13].setState(nts::UNDEFINED);
    } else if (this->value[9].getState() != nts::FALSE) {
        if (this->value[9].getState() == nts::TRUE) {
            this->value[13].setState(nts::FALSE);
        } else {
            this->value[13].setState(nts::UNDEFINED);
        }
    } else if (this->value[11].getState() == nts::UNDEFINED || this->value[12].getState() == nts::UNDEFINED || this->value[10].getState() == nts::UNDEFINED){
        this->value[13].setState(nts::UNDEFINED);
    } else {
        size_t stock = (this->value[10].getState() * 1) + (this->value[11].getState() * 2) + (this->value[12].getState() * 4);
        if (stock == 7) {
            this->value[13].setState(this->value[8].getState());
        } else {
            this->value[13].setState(this->value[stock].getState());
        }
    }
    if (pin < this->size) {
        return (this->value[pin].getState());
    } else {
        return (nts::UNDEFINED);
    }
}

std::string C_4512::getType() const
{
    return "4512";
}
