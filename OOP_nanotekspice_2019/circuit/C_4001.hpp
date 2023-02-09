/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_4001
*/

#ifndef C_4001_HPP_
#define C_4001_HPP_

#include "../Circuit.hpp"
#include "../IComponent.hpp"

namespace nts {
    enum Tristate;
    class IComponent;
}

class C_4001 : public Circuit {
    public:
        C_4001(const std::string &value);
        ~C_4001();
        nts::Tristate compute(std::size_t pin = 1) final;
        std::string getType() const final;

    protected:
    private:
};

#endif /* !C_4001_HPP_ */
