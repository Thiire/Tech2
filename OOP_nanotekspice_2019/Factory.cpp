/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Factory
*/

#include "Factory.hpp"

std::unique_ptr<nts::IComponent> Factory::createComponent(const std::string &type, const std::string &value)
{
    if (type == "2716") {
        return (this->create2716(value));
    } else if (type == "4001") {
        return (this->create4001(value));
    } else if (type == "4008") {
        return (this->create4008(value));
    } else if (type == "4011") {
        return (this->create4011(value));
    } else if (type == "4013") {
        return (this->create4013(value));
    } else if (type == "4017") {
        return (this->create4017(value));
    } else if (type == "4030") {
        return (this->create4030(value));
    } else if (type == "4040") {
        return (this->create4040(value));
    } else if (type == "4069") {
        return (this->create4069(value));
    } else if (type == "4071") {
        return (this->create4071(value));
    } else if (type == "4081") {
        return (this->create4081(value));
    } else if (type == "4094") {
        return (this->create4094(value));
    } else if (type == "4503") {
        return (this->create4503(value));
    } else if (type == "4512") {
        return (this->create4512(value));
    } else if (type == "4514") {
        return (this->create4514(value));
    } else if (type == "i4004") {
        return (this->createi4004(value));
    } else if (type == "mk4801") {
        return (this->createmk4801(value));
    } else {
        std::cerr << "This circuit [" << type << "] doesn't exist" << std::endl;
        exit(84);
    }
}

std::unique_ptr<nts::IComponent> Factory::create2716(const std::string &value) const noexcept
{
    return (std::make_unique<C_2716>(value));
}

std::unique_ptr<nts::IComponent> Factory::create4001(const std::string &value) const noexcept
{
    return (std::make_unique<C_4001>(value));
}

std::unique_ptr<nts::IComponent> Factory::create4008(const std::string &value) const noexcept
{
    return (std::make_unique<C_4008>(value));
}

std::unique_ptr<nts::IComponent> Factory::create4011(const std::string &value) const noexcept
{
    return (std::make_unique<C_4011>(value));
}

std::unique_ptr<nts::IComponent> Factory::create4013(const std::string &value) const noexcept
{
    return (std::make_unique<C_4013>(value));
}

std::unique_ptr<nts::IComponent> Factory::create4017(const std::string &value) const noexcept
{
    return (std::make_unique<C_4017>(value));
}

std::unique_ptr<nts::IComponent> Factory::create4030(const std::string &value) const noexcept
{
    return (std::make_unique<C_4030>(value));
}

std::unique_ptr<nts::IComponent> Factory::create4040(const std::string &value) const noexcept
{
    return (std::make_unique<C_4040>(value));
}

std::unique_ptr<nts::IComponent> Factory::create4069(const std::string &value) const noexcept
{
    return (std::make_unique<C_4069>(value));
}

std::unique_ptr<nts::IComponent> Factory::create4071(const std::string &value) const noexcept
{
    return (std::make_unique<C_4071>(value));
}

std::unique_ptr<nts::IComponent> Factory::create4081(const std::string &value) const noexcept
{
    return (std::make_unique<C_4081>(value));
}

std::unique_ptr<nts::IComponent> Factory::create4094(const std::string &value) const noexcept
{
    return (std::make_unique<C_4094>(value));
}

std::unique_ptr<nts::IComponent> Factory::create4503(const std::string &value) const noexcept
{
    return (std::make_unique<C_4503>(value));
}

std::unique_ptr<nts::IComponent> Factory::create4512(const std::string &value) const noexcept
{
    return (std::make_unique<C_4512>(value));
}

std::unique_ptr<nts::IComponent> Factory::create4514(const std::string &value) const noexcept
{
    return (std::make_unique<C_4514>(value));
}

std::unique_ptr<nts::IComponent> Factory::createi4004(const std::string &value) const noexcept
{
    return (std::make_unique<C_i4004>(value));
}

std::unique_ptr<nts::IComponent> Factory::createmk4801(const std::string &value) const noexcept
{
    return (std::make_unique<C_mk4801>(value));
}
