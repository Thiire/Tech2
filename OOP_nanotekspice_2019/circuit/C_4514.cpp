/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4514
*/

#include "C_4514.hpp"

C_4514::C_4514(const std::string &value)
{
    this->size = 24;
    this->value = std::vector<Pin>(24);
    this->value[1].setType(nts::input);
    this->value[2].setType(nts::input);
    this->value[20].setType(nts::input);
    this->value[21].setType(nts::input);
    this->value[3].setType(nts::output);
    this->value[4].setType(nts::output);
    this->value[5].setType(nts::output);
    this->value[6].setType(nts::output);
    this->value[7].setType(nts::output);
    this->value[8].setType(nts::output);
    this->value[9].setType(nts::output);
    this->value[10].setType(nts::output);
    this->value[12].setType(nts::output);
    this->value[13].setType(nts::output);
    this->value[14].setType(nts::output);
    this->value[15].setType(nts::output);
    this->value[16].setType(nts::output);
    this->value[17].setType(nts::output);
    this->value[18].setType(nts::output);
    this->value[19].setType(nts::output);
    this->value[22].setType(nts::input);
    this->value[0].setType(nts::input);
}

C_4514::~C_4514()
{
}

nts::Tristate C_4514::compute(std::size_t pin)
{
    if (this->value[0].getState()) {
        if (this->value[22].getState()) {
            for (size_t i = 0; i < this->size; i++) {
                if (this->value[i].getType() == "output") {
                    this->value[i].setState(nts::FALSE);
                }
            }
        } else {
            size_t stock = (this->value[1].getState() * 1) + (this->value[2].getState() * 2) + (this->value[20].getState() * 4) + (this->value[20].getState() * 8);
            if (stock == 0) {
                this->value[10].setState(nts::TRUE);
            } else if (stock == 1) {
                this->value[8].setState(nts::TRUE);
            } else if (stock == 2) {
                this->value[9].setState(nts::TRUE);
            } else if (stock == 3) {
                this->value[7].setState(nts::TRUE);
            } else if (stock == 4) {
                this->value[6].setState(nts::TRUE);
            } else if (stock == 5) {
                this->value[5].setState(nts::TRUE);
            } else if (stock == 6) {
                this->value[4].setState(nts::TRUE);
            } else if (stock == 7) {
                this->value[3].setState(nts::TRUE);
            } else if (stock == 8) {
                this->value[17].setState(nts::TRUE);
            } else if (stock == 9) {
                this->value[16].setState(nts::TRUE);
            } else if (stock == 10) {
                this->value[19].setState(nts::TRUE);
            } else if (stock == 11) {
                this->value[18].setState(nts::TRUE);
            } else if (stock == 12) {
                this->value[13].setState(nts::TRUE);
            } else if (stock == 13) {
                this->value[12].setState(nts::TRUE);
            } else if (stock == 14) {
                this->value[15].setState(nts::TRUE);
            } else if (stock == 15) {
                this->value[14].setState(nts::TRUE);
            }
        }
    }
    if (pin < this->size) {
        return (this->value[pin].getState());
    } else {
        return (nts::UNDEFINED);
    }
}

std::string C_4514::getType() const
{
    return "4514";
}
