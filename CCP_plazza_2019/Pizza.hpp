/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pizza
*/

#ifndef PIZZA_HPP_
#define PIZZA_HPP_

#include <string>
#include <iostream>
#include <fstream>

enum PizzaType
{
    undefined = -1,
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8,
};

enum PizzaSize
{
    UNDEFINED = -1,
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16,
};

template<class T, class Y>
class Pizza {
    public:
        Pizza(const T &type, const Y &size);
        Pizza(const int &type, const int &size);
        ~Pizza();
        const PizzaType &getType() const;
        const PizzaSize &getSize() const;
        const T getSizeStr() const;
        const T getTypeStr() const;

    protected:
    private:
        PizzaSize _size;
        PizzaType _type;
};

#endif /* !PIZZA_HPP_ */
