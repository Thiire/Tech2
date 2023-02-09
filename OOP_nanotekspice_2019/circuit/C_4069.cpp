/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4069
*/

#include "C_4069.hpp"

C_4069::C_4069(const std::string &value)
{
    this->size = 14;
    this->value = std::vector<Pin>(14);
    this->value[0].setType(nts::input);
    this->value[1].setType(nts::output);
    this->value[2].setType(nts::input);
    this->value[3].setType(nts::output);
    this->value[4].setType(nts::input);
    this->value[5].setType(nts::output);
    this->value[7].setType(nts::output);
    this->value[8].setType(nts::input);
    this->value[9].setType(nts::output);
    this->value[10].setType(nts::input);
    this->value[11].setType(nts::output);
    this->value[12].setType(nts::input);
}

C_4069::~C_4069()
{
}

nts::Tristate C_4069::compute(std::size_t pin)
{
    if (this->value[0].getState()) {
        this->value[1].setState(nts::FALSE);
    } else if (this->value[0].getState() == nts::UNDEFINED) {
        this->value[1].setState(nts::UNDEFINED);
    } else {
        this->value[1].setState(nts::TRUE);
    }
    if (this->value[2].getState()) {
        this->value[3].setState(nts::FALSE);
    } else if (this->value[2].getState() == nts::UNDEFINED) {
        this->value[1].setState(nts::UNDEFINED);
    } else {
        this->value[3].setState(nts::TRUE);
    }
    if (this->value[4].getState()) {
        this->value[5].setState(nts::FALSE);
    } else if (this->value[4].getState() == nts::UNDEFINED) {
        this->value[1].setState(nts::UNDEFINED);
    } else {
        this->value[5].setState(nts::TRUE);
    }
    if (this->value[8].getState()) {
        this->value[7].setState(nts::FALSE);
    } else if (this->value[8].getState() == nts::UNDEFINED) {
        this->value[1].setState(nts::UNDEFINED);
    } else {
        this->value[7].setState(nts::TRUE);
    }
    if (this->value[10].getState()) {
        this->value[9].setState(nts::FALSE);
    } else if (this->value[10].getState() == nts::UNDEFINED) {
        this->value[1].setState(nts::UNDEFINED);
    } else {
        this->value[9].setState(nts::TRUE);
    }
    if (this->value[12].getState()) {
        this->value[11].setState(nts::FALSE);
    } else if (this->value[12].getState() == nts::UNDEFINED) {
        this->value[1].setState(nts::UNDEFINED);
    } else {
        this->value[11].setState(nts::TRUE);
    }
    if (pin < this->size) {
        return (this->value[pin].getState());
    } else {
        return (nts::UNDEFINED);
    }
}

std::string C_4069::getType() const
{
    return "4069";
}
