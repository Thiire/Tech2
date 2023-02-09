/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Pin
*/

#ifndef PIN_HPP_
#define PIN_HPP_

#include "IComponent.hpp"

class Pin : public nts::IComponent {
    public:
        Pin(const std::string type = "UNUSED", const nts::Tristate value = nts::UNDEFINED);

        bool isPin() const final {return true;};
        std::size_t getSize() const final {return 1;};
        nts::IComponent &getPin(std::size_t number) final;
        nts::Tristate getState() const final {return *this->state;};
        std::string getType() const final;
        void setType(nts::Tritype value) final;
        void setState(nts::Tristate value) final;

        std::shared_ptr<nts::Tristate> getShared() const {return this->state;};
        void setShared(std::shared_ptr<nts::Tristate> value) {this->state = value;};

        nts::Tristate compute(std::size_t pin = 1) final;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) final;
        void dump() const final;
    protected:
    private:
        nts::Tritype type;
        std::shared_ptr<nts::Tristate> state;
};

#endif /* !PIN_HPP_ */
