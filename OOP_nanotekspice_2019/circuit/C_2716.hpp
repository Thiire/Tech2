/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_2716
*/

#ifndef C_2716_HPP_
#define C_2716_HPP_

#include "../Circuit.hpp"
#include "../IComponent.hpp"

namespace nts {
    enum Tristate;
    class IComponent;
}

class C_2716 : public Circuit {
    public:
        C_2716(const std::string &value);
        ~C_2716();
        nts::Tristate compute(std::size_t pin = 1) final;
        std::string getType() const final;

    protected:
    private:
};

#endif /* !C_2716_HPP_ */
