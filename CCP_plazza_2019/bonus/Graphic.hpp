/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Graphic
*/

#ifndef GRAPHIC_HPP_
#define GRAPHIC_HPP_

#include "Recep2.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <string>

enum Input {
    NONE = -1,
    KEY_LEFT,
    KEY_RIGHT,
    EXIT,
    ENTER,
};

class Graphic {
    public:
        Graphic(int multiplier, int cook = 5, int time = 2000);
        ~Graphic();
        void start();
        void draw();
        void drawCook();
        void getPizzaInput();
        bool getSendState() const;
        void draw_pizza_size();
        Input getInput();
        void manageSelection();
        void setKeyDown();
        void setInputPizza();
        void draw_quantity();
    protected:
    private:
        bool _isSend;
        Recep _recep;
        std::vector<ALLEGRO_BITMAP *> _pizzaSprites;
        ALLEGRO_DISPLAY *_display;
        ALLEGRO_COLOR _colorInput;
        ALLEGRO_KEYBOARD_STATE _key;
        ALLEGRO_EVENT_QUEUE* q;
        ALLEGRO_EVENT evt;
        std::string _pizzaInput;
        ALLEGRO_FONT *_font_Title;
        ALLEGRO_FONT *_font;
        int _choosePizza;
        int _chooseSize;
        std::string _chooseQuantity;
        int _side;
        bool _keyDown;

};

#endif /* !GRAPHIC_HPP_ */
