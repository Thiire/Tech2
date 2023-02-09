/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** C_mk4801
*/

#ifndef C_MK4801_HPP_
#define C_MK4801_HPP_

#include "../Circuit.hpp"
#include "../IComponent.hpp"

namespace nts {
    enum Tristate;
    class IComponent;
}

class C_mk4801 : public Circuit {
    public:
        C_mk4801(const std::string &value);
        ~C_mk4801();
        nts::Tristate compute(std::size_t pin = 1) final;
        std::string getType() const final;

    protected:
    private:
};

#endif /* !C_MK4801_HPP_ */
