/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include "IComponent.hpp"
#include "circuit/C_2716.hpp"
#include "circuit/C_4001.hpp"
#include "circuit/C_4008.hpp"
#include "circuit/C_4011.hpp"
#include "circuit/C_4013.hpp"
#include "circuit/C_4017.hpp"
#include "circuit/C_4030.hpp"
#include "circuit/C_4040.hpp"
#include "circuit/C_4069.hpp"
#include "circuit/C_4071.hpp"
#include "circuit/C_4081.hpp"
#include "circuit/C_4094.hpp"
#include "circuit/C_4503.hpp"
#include "circuit/C_4512.hpp"
#include "circuit/C_4514.hpp"
#include "circuit/C_i4004.hpp"
#include "circuit/C_mk4801.hpp"

namespace nts {
    class IComponent;
}

class Factory {
    public:
        std::unique_ptr<nts::IComponent> createComponent(const std::string &type, const std::string &value);
    protected:
    private:
        std::unique_ptr<nts::IComponent> create2716(const std::string &value) const noexcept;
        std::unique_ptr<nts::IComponent> create4001(const std::string &value) const noexcept;
        std::unique_ptr<nts::IComponent> create4008(const std::string &value) const noexcept;
        std::unique_ptr<nts::IComponent> create4011(const std::string &value) const noexcept;
        std::unique_ptr<nts::IComponent> create4013(const std::string &value) const noexcept;
        std::unique_ptr<nts::IComponent> create4017(const std::string &value) const noexcept;
        std::unique_ptr<nts::IComponent> create4030(const std::string &value) const noexcept;
        std::unique_ptr<nts::IComponent> create4040(const std::string &value) const noexcept;
        std::unique_ptr<nts::IComponent> create4069(const std::string &value) const noexcept;
        std::unique_ptr<nts::IComponent> create4071(const std::string &value) const noexcept;
        std::unique_ptr<nts::IComponent> create4081(const std::string &value) const noexcept;
        std::unique_ptr<nts::IComponent> create4094(const std::string &value) const noexcept;
        std::unique_ptr<nts::IComponent> create4503(const std::string &value) const noexcept;
        std::unique_ptr<nts::IComponent> create4512(const std::string &value) const noexcept;
        std::unique_ptr<nts::IComponent> create4514(const std::string &value) const noexcept;
        std::unique_ptr<nts::IComponent> createi4004(const std::string &value) const noexcept;
        std::unique_ptr<nts::IComponent> createmk4801(const std::string &value) const noexcept;
};

#endif /* !FACTORY_HPP_ */
