/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4071
*/

#ifndef C_4071_HPP_
#define C_4071_HPP_

#include "../Circuit.hpp"
#include "../IComponent.hpp"

namespace nts {
    enum Tristate;
    class IComponent;
}

class C_4071 : public Circuit {
    public:
        C_4071(const std::string &value);
        ~C_4071();
        nts::Tristate compute(std::size_t pin = 1) final;
        std::string getType() const final;

    protected:
    private:
};

#endif /* !C_4071_HPP_ */
