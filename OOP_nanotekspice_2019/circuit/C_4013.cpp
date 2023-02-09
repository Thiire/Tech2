/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4013
*/

#include "C_4013.hpp"

C_4013::C_4013(const std::string &value)
{
    this->size = 14;
    this->value = std::vector<Pin>(14);
    this->value[8].setType(nts::input);
    this->value[4].setType(nts::input);
    this->value[7].setType(nts::input);
    this->value[5].setType(nts::input);
    this->value[9].setType(nts::input);
    this->value[3].setType(nts::input);
    this->value[2].setType(nts::clock);
    this->value[10].setType(nts::clock);
    this->value[0].setType(nts::output);
    this->value[1].setType(nts::output);
    this->value[11].setType(nts::output);
    this->value[12].setType(nts::output);
}

C_4013::~C_4013()
{
}

nts::Tristate C_4013::compute(std::size_t pin)
{
    if (this->value[2].getState() == 1) {
        this->value[2].setState(nts::FALSE);
    } else {
        this->value[2].setState(nts::TRUE);
    }
    if (this->value[10].getState() == 1) {
        this->value[10].setState(nts::FALSE);
    } else {
        this->value[10].setState(nts::TRUE);
    }

    if (this->value[9].getState() == nts::UNDEFINED || this->value[7].getState() == nts::UNDEFINED) {
        this->value[11].setState(nts::UNDEFINED);
        this->value[12].setState(nts::UNDEFINED);
    }
    if (this->value[9].getState() || this->value[7].getState()) {
        if (this->value[9].getState() && this->value[7].getState()) {
            this->value[11].setState(nts::TRUE);
            this->value[12].setState(nts::TRUE);
        } else if (this->value[9].getState()) {
            this->value[11].setState(nts::TRUE);
            this->value[12].setState(nts::FALSE);
        } else {
            this->value[11].setState(nts::FALSE);
            this->value[12].setState(nts::TRUE);
        }
    } else if (!this->value[10].getState()) {

    } else {
        if (this->value[8].getState()) {
            this->value[11].setState(nts::FALSE);
            this->value[12].setState(nts::TRUE);
        } else if (!this->value[8].getState()) {
            this->value[11].setState(nts::TRUE);
            this->value[12].setState(nts::FALSE);
        } else {
            this->value[11].setState(nts::UNDEFINED);
            this->value[12].setState(nts::UNDEFINED);
        }
    }

    if (this->value[3].getState() == nts::UNDEFINED || this->value[5].getState() == nts::UNDEFINED) {
        this->value[1].setState(nts::UNDEFINED);
        this->value[0].setState(nts::UNDEFINED);
    }
    if (this->value[3].getState() || this->value[5].getState()) {
        if (this->value[3].getState() && this->value[5].getState()) {
            this->value[1].setState(nts::TRUE);
            this->value[0].setState(nts::TRUE);
        } else if (this->value[3].getState()) {
            this->value[1].setState(nts::TRUE);
            this->value[0].setState(nts::FALSE);
        } else {
            this->value[1].setState(nts::FALSE);
            this->value[0].setState(nts::TRUE);
        }
    } else if (!this->value[2].getState()) {

    } else {
        if (this->value[4].getState()) {
            this->value[1].setState(nts::FALSE);
            this->value[0].setState(nts::TRUE);
        } else if (!this->value[4].getState()) {
            this->value[1].setState(nts::TRUE);
            this->value[0].setState(nts::FALSE);
        } else {
            this->value[1].setState(nts::UNDEFINED);
            this->value[0].setState(nts::UNDEFINED);
        }
    }
    
    if (pin < this->size) {
        return (this->value[pin].getState());
    } else {
        return (nts::UNDEFINED);
    }
}

std::string C_4013::getType() const
{
    return "4013";
}
