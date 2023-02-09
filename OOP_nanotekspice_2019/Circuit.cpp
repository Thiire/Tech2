/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Circuit
*/

#include "Circuit.hpp"

Circuit::Circuit()
{
    this->size = 0;
    this->type = "UNDEFINED";
}

nts::IComponent &Circuit::getPin(std::size_t number)
{
    if (this->getSize() < number) {
        std::cerr << "Not enough pin on this circuit" << std::endl;
        exit(84);
    } else {
        return (this->value[number - 1]);
    }
}

void Circuit::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (this->getSize() < pin) {
        std::cerr << "Not enough pin on this circuit" << std::endl;
        exit(84);
    } else {
        this->value[pin - 1].setShared(dynamic_cast<Pin&>(other.getPin(otherPin)).getShared());
    }
}

void Circuit::dump() const
{
    for (size_t i = 0; i < this->getSize(); i++) {
        std::cout << "  [" << i + 1 << "]: ";
        this->value[i].dump();
    }
}

nts::Tristate AND(nts::Tristate va1, nts::Tristate va2)
{
    if (va1 && va2) {
        return nts::TRUE;
    } else if (va1 == nts::UNDEFINED || va2 == nts::UNDEFINED) {
        return nts::UNDEFINED;
    } else {
        return nts::FALSE;
    }
}

nts::Tristate OR(nts::Tristate va1, nts::Tristate va2)
{
    if (va1 == nts::UNDEFINED || va2 == nts::UNDEFINED) {
        return nts::UNDEFINED;
    } else if (va1 || va2) {
        return nts::TRUE;
    } else {
        return nts::FALSE;
    }
}

nts::Tristate XOR(nts::Tristate va1, nts::Tristate va2)
{
    if (va1 == nts::UNDEFINED || va2 == nts::UNDEFINED) {
        return nts::UNDEFINED;
    } else if (va1 == va2) {
        return nts::FALSE;
    } else {
        return nts::TRUE;
    }
}

nts::Tristate NAND(nts::Tristate va1, nts::Tristate va2)
{
    if (va1 == nts::UNDEFINED || va2 == nts::UNDEFINED) {
        return nts::UNDEFINED;
    } else if (va1 && va2) {
        return nts::FALSE;
    } else {
        return nts::TRUE;
    }
}

nts::Tristate NOR(nts::Tristate va1, nts::Tristate va2)
{
    if (va1 == nts::UNDEFINED || va2 == nts::UNDEFINED) {
        return nts::UNDEFINED;
    } else if (va1 || va2) {
        return nts::FALSE;
    } else {
        return nts::TRUE;
    }
}
