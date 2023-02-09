/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4514
*/

#ifndef C_4514_HPP_
#define C_4514_HPP_

#include "../Circuit.hpp"
#include "../IComponent.hpp"

namespace nts {
    enum Tristate;
    class IComponent;
}

class C_4514 : public Circuit {
    public:
        C_4514(const std::string &value);
        ~C_4514();
        nts::Tristate compute(std::size_t pin = 1) final;
        std::string getType() const final;

    protected:
    private:
};

#endif /* !C_4514_HPP_ */
