/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Circuit
*/

#ifndef CIRCUIT_HPP_
#define CIRCUIT_HPP_

#include "IComponent.hpp"
#include "Pin.hpp"

class Pin;
namespace nts {
    enum Tristate;
    enum Tritype;
    class IComponent;
}


nts::Tristate AND(nts::Tristate va1, nts::Tristate va2);
nts::Tristate OR(nts::Tristate va1, nts::Tristate va2);
nts::Tristate XOR(nts::Tristate va1, nts::Tristate va2);
nts::Tristate NAND(nts::Tristate va1, nts::Tristate va2);
nts::Tristate NOR(nts::Tristate va1, nts::Tristate va2);

class Circuit : public nts::IComponent {
    public:
        Circuit();
        bool isPin() const final {return false;};
        std::size_t getSize() const final {return this->size;};
        nts::IComponent &getPin(std::size_t number) final;
        nts::Tristate getState() const final {return nts::UNDEFINED;};
        virtual std::string getType() const = 0;
        void setType(nts::Tritype value) final {};
        void setState(nts::Tristate value) final {};

        virtual nts::Tristate compute(std::size_t pin = 1) = 0;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) final;
        void dump() const final;

    protected:
        std::vector<Pin> value;
        std::size_t size;
    private:
        std::string type;
};

#endif /* !CIRCUIT_HPP_ */
