/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_i4004
*/

#ifndef C_I4004_HPP_
#define C_I4004_HPP_

#include "../Circuit.hpp"
#include "../IComponent.hpp"

namespace nts {
    enum Tristate;
    class IComponent;
}

class C_i4004 : public Circuit {
    public:
        C_i4004(const std::string &value);
        ~C_i4004();
        nts::Tristate compute(std::size_t pin = 1) final;
        std::string getType() const final;

    protected:
    private:
};

#endif /* !C_I4004_HPP_ */
