/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4030
*/

#ifndef C_4030_HPP_
#define C_4030_HPP_

#include "../Circuit.hpp"
#include "../IComponent.hpp"

namespace nts {
    enum Tristate;
    class IComponent;
}

class C_4030 : public Circuit {
    public:
        C_4030(const std::string &value);
        ~C_4030();
        nts::Tristate compute(std::size_t pin = 1) final;
        std::string getType() const final;

    protected:
    private:
};

#endif /* !C_4030_HPP_ */
