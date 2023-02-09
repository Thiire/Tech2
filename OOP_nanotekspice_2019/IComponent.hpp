/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

#include <string>
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

namespace nts {
    enum Tristate {UNDEFINED = (-true), TRUE = true, FALSE = false};
    enum Tritype {UNUSED = (-true), input, output, _true, _false, clock};
    class IComponent {
    public :
        virtual ~IComponent() = default;

    public :
        virtual nts::Tristate compute(std::size_t pin = 1) = 0;
        virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) = 0;
        virtual void dump() const = 0;

    public:
        virtual bool isPin() const = 0;
        virtual std::size_t getSize() const = 0;
        virtual IComponent &getPin(std::size_t number) = 0;
        virtual Tristate getState() const = 0;
        virtual std::string getType() const = 0;
        virtual void setType(Tritype value) = 0;
        virtual void setState(Tristate value) = 0;

    };
}

#endif /* !ICOMPONENT_HPP_ */
