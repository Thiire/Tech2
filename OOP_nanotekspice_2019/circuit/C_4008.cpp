/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4008
*/

#include "C_4008.hpp"

C_4008::C_4008(const std::string &value)
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
    this->value[9].setType(nts::output);
    this->value[10].setType(nts::output);
    this->value[11].setType(nts::output);
    this->value[12].setType(nts::output);
    this->value[14].setType(nts::input);
}

C_4008::~C_4008()
{
}

nts::Tristate C_4008::compute(std::size_t pin)
{
    nts::Tristate c2(nts::UNDEFINED);
    nts::Tristate c3(nts::UNDEFINED);
    nts::Tristate c4(nts::UNDEFINED);
    size_t stock = 0;

    if (this->value[5].getState() == nts::UNDEFINED || this->value[6].getState() == nts::UNDEFINED || this->value[8].getState() == nts::UNDEFINED) {
        c2 = nts::UNDEFINED;
        this->value[9].setState(nts::UNDEFINED);
    } else {
        stock = this->value[5].getState() + this->value[6].getState() + this->value[8].getState();
        if (stock == 0) {
            c2 = nts::FALSE;
            this->value[9].setState(nts::FALSE);
        } else if (stock == 1) {
            c2 = nts::FALSE;
            this->value[9].setState(nts::TRUE);
        } else if (stock == 2) {
            c2 = nts::TRUE;
            this->value[9].setState(nts::FALSE);
        } else {
            c2 = nts::TRUE;
            this->value[9].setState(nts::TRUE);
        }
    }
    if (this->value[3].getState() == nts::UNDEFINED || this->value[4].getState() == nts::UNDEFINED || c2 == nts::UNDEFINED) {
        c3 = nts::UNDEFINED;
        this->value[10].setState(nts::UNDEFINED);
    } else {
        stock = this->value[3].getState() + this->value[4].getState() + c2;
        if (stock == 0) {
            c3 = nts::FALSE;
            this->value[10].setState(nts::FALSE);
        } else if (stock == 1) {
            c3 = nts::FALSE;
            this->value[10].setState(nts::TRUE);
        } else if (stock == 2) {
            c3 = nts::TRUE;
            this->value[10].setState(nts::FALSE);
        } else {
            c3 = nts::TRUE;
            this->value[10].setState(nts::TRUE);
        }
    }
    if (this->value[1].getState() == nts::UNDEFINED || this->value[2].getState() == nts::UNDEFINED || c3 == nts::UNDEFINED) {
        c4 = nts::UNDEFINED;
        this->value[11].setState(nts::UNDEFINED);
    } else {
        stock = this->value[3].getState() + this->value[4].getState() + c3;
        if (stock == 0) {
            c4 = nts::FALSE;
            this->value[11].setState(nts::FALSE);
        } else if (stock == 1) {
            c4 = nts::FALSE;
            this->value[11].setState(nts::TRUE);
        } else if (stock == 2) {
            c4 = nts::TRUE;
            this->value[11].setState(nts::FALSE);
        } else {
            c4 = nts::TRUE;
            this->value[11].setState(nts::TRUE);
        }
    }
    if (this->value[14].getState() == nts::UNDEFINED || this->value[0].getState() == nts::UNDEFINED || c4 == nts::UNDEFINED) {
        this->value[12].setState(nts::UNDEFINED);
    } else {
        stock = this->value[14].getState() + this->value[0].getState() + c4;
        if (stock == 0) {
            this->value[13].setState(nts::FALSE);
            this->value[12].setState(nts::FALSE);
        } else if (stock == 1) {
            this->value[13].setState(nts::FALSE);
            this->value[12].setState(nts::TRUE);
        } else if (stock == 2) {
            this->value[13].setState(nts::TRUE);
            this->value[12].setState(nts::FALSE);
        } else {
            this->value[13].setState(nts::TRUE);
            this->value[12].setState(nts::TRUE);
        }
    }
    if (pin < this->size) {
        return (this->value[pin].getState());
    } else {
        return (nts::UNDEFINED);
    }
}

std::string C_4008::getType() const
{
    return "4008";
}
