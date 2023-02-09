/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Pizza
*/

#include "Pizza.hpp"

template Pizza<std::string, std::string>::Pizza(const std::string &type, const std::string &size);
template Pizza<std::string, std::string>::Pizza(const int &type, const int &size);
template Pizza<std::string, std::string>::~Pizza();
template const PizzaSize &Pizza<std::string, std::string>::getSize() const;
template const PizzaType &Pizza<std::string, std::string>::getType() const;
template const std::string Pizza<std::string, std::string>::getSizeStr() const;
template const std::string Pizza<std::string, std::string>::getTypeStr() const;

template<class T, class Y>
Pizza<T, Y>::Pizza(const T &type, const Y &size)
{
    if (!type.compare("Regina")) {
        this->_type = PizzaType::Regina;
    } else if (!type.compare("Margarita")) {
        this->_type = PizzaType::Margarita;
    } else if (!type.compare("Americana")) {
        this->_type = PizzaType::Americana;
    } else if (!type.compare("Fantasia")) {
        this->_type = PizzaType::Fantasia;
    } else {
        exit(84);
    }
    if (!size.compare("S")) {
        this->_size = PizzaSize::S;
    } else if (!size.compare("M")) {
        this->_size = PizzaSize::M;
    } else if (!size.compare("L")) {
        this->_size = PizzaSize::L;
    } else if (!size.compare("XL")) {
        this->_size = PizzaSize::XL;
    } else if (!size.compare("XXL")) {
        this->_size = PizzaSize::XXL;
    } else {
        exit(84);
    }
}

template<class T, class Y>
Pizza<T, Y>::Pizza(const int &type, const int &size)
{
    this->_size = PizzaSize(size);
    this->_type = PizzaType(type);
}

template<class T, class Y>
Pizza<T, Y>::~Pizza()
{
}

template<class T, class Y>
const T Pizza<T, Y>::getSizeStr() const
{
    switch (this->_size) {
        case -1:
            return "UNDEFINED";
        case 1:
            return "S";
        case 2:
            return "M";
        case 4:
            return "L";
        case 8:
            return "XL";
        case 16:
            return "XXL";
        default:
            return "Not Defined";
    }
}

template<class T, class Y>
const T Pizza<T, Y>::getTypeStr() const
{
    switch (this->_type) {
        case -1:
            return "UNDEFINED";
        case 1:
            return "Regina";
        case 2:
            return "Margarita";
        case 4:
            return "Americana";
        case 8:
            return "Fantasia";
        default:
            return "Not Defined";
    }
}

template<class T, class Y>
const PizzaSize &Pizza<T, Y>::getSize() const
{
    return this->_size;
}

template<class T, class Y>
const PizzaType &Pizza<T, Y>::getType() const
{
    return this->_type;
}
