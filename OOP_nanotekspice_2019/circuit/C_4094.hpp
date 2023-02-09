/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4094
*/

#ifndef C_4094_HPP_
#define C_4094_HPP_

#include "../Circuit.hpp"
#include "../IComponent.hpp"

namespace nts {
    enum Tristate;
    class IComponent;
}

class C_4094 : public Circuit {
    public:
        C_4094(const std::string &value);
        ~C_4094();
        nts::Tristate compute(std::size_t pin = 1) final;
        std::string getType() const final;

    protected:
    private:
};

#endif /* !C_4094_HPP_ */
