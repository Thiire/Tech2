/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4503
*/

#ifndef C_4503_HPP_
#define C_4503_HPP_

#include "../Circuit.hpp"
#include "../IComponent.hpp"

namespace nts {
    enum Tristate;
    class IComponent;
}

class C_4503 : public Circuit {
    public:
        C_4503(const std::string &value);
        ~C_4503();
        nts::Tristate compute(std::size_t pin = 1) final;
        std::string getType() const final;

    protected:
    private:
};

#endif /* !C_4503_HPP_ */
