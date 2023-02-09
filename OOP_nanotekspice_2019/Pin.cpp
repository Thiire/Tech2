/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Pin
*/

#include "Pin.hpp"

Pin::Pin(const std::string type, const nts::Tristate value)
{
    if (!type.compare("UNUSED")) {
        this->setType(nts::UNUSED);
    } else if (!type.compare("input")) {
        this->setType(nts::input);
    } else if (!type.compare("output")) {
        this->setType(nts::output);
    } else if (!type.compare("true")) {
        this->setType(nts::_true);
    } else if (!type.compare("false")) {
        this->setType(nts::_false);
    } else if (!type.compare("clock")) {
        this->setType(nts::clock);
    } else {
        std::cerr << "Type [" << type << "] is unvalid, valid one is : input, output, true, false, clock" << std::endl;
    }
}

nts::IComponent &Pin::getPin(std::size_t number)
{
    if (number != 1) {
        std::cerr << "There is only 1 pin available for Input / Output" << std::endl;
        exit(84);
    } else {
        return (*this);
    }
}

std::string Pin::getType() const
{
    if (this->type == nts::input) {
        return "input";
    } else if (this->type == nts::output) {
        return "output";
    } else if (this->type == nts::_true) {
        return "true";
    } else if (this->type == nts::_false) {
        return "false";
    } else if (this->type == nts::clock) {
        return "clock";
    } else if (this->type == nts::UNUSED) {
        return "unused";
    }
}

void Pin::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (this->type == nts::output) {
        if (pin == 1) {
            this->state = dynamic_cast<Pin&>(other.getPin(otherPin)).state;
        } else {
            std::cerr << "Output only have 1 pin" << std::endl;
            exit(84);
        }
    } else {
        std::cerr << "Impossible to link non output pin" << std::endl;
        exit(84);
    }
}

void Pin::dump() const
{
    std::cout << this->getType() << " = " << this->getState() << std::endl;
}

nts::Tristate Pin::compute(std::size_t pin)
{

}

void Pin::setType(nts::Tritype value)
{
    if (value == nts::UNUSED) {
        this->type = value;
        this->state = std::make_unique<nts::Tristate>(nts::UNDEFINED);
    } else if (value == nts::input) {
        this->type = value;
        this->state = std::make_unique<nts::Tristate>(nts::UNDEFINED);
    } else if (value == nts::output) {
        this->type = value;
        this->state = std::make_unique<nts::Tristate>(nts::UNDEFINED);
    } else if (value == nts::_true) {
        this->type = value;
        this->state = std::make_unique<nts::Tristate>(nts::TRUE);
    } else if (value == nts::_false) {
        this->type = value;
        this->state = std::make_unique<nts::Tristate>(nts::FALSE);
    } else if (value == nts::clock) {
        this->type = value;
        this->state = std::make_unique<nts::Tristate>(nts::FALSE);
    } else {
        this->type = nts::UNUSED;
        this->state = std::make_unique<nts::Tristate>(nts::UNDEFINED);
    }
}

void Pin::setState(nts::Tristate value)
{
    *this->state = value;
}
