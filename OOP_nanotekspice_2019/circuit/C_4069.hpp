/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4069
*/

#ifndef C_4069_HPP_
#define C_4069_HPP_

#include "../Circuit.hpp"
#include "../IComponent.hpp"

namespace nts {
    enum Tristate;
    class IComponent;
}

class C_4069 : public Circuit {
    public:
        C_4069(const std::string &value);
        ~C_4069();
        nts::Tristate compute(std::size_t pin = 1) final;
        std::string getType() const final;

    protected:
    private:
};

#endif /* !C_4069_HPP_ */
