/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Graphic
*/

#include "Graphic.hpp"

Graphic::Graphic(int multiplier, int cook, int time) : _recep(multiplier, cook, time)
{
    _pizzaInput = "";
    _choosePizza = 0;
    _chooseQuantity = "";
    _chooseSize = -1;
    _keyDown = false;
    _side = 0;
    al_install_system(ALLEGRO_VERSION_INT, atexit);
    if (!al_init())
        al_show_native_message_box(NULL, "Erreur", "Error Init", "Could not initialize", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    _font_Title = al_load_font("./assets/pizzeria.ttf", 50, 0);
    _font = al_load_font("./assets/font.ttf", 35, 0);

    _display = al_create_display(1920, 1080);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    al_install_keyboard();
    _colorInput = al_map_rgb(255, 255, 255);
    if (!_display)
        al_show_native_message_box(NULL, "Erreur", "Error Display", "Could not Display", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    q = al_create_event_queue();
    al_register_event_source(q, al_get_keyboard_event_source());
        al_init_image_addon();
    _pizzaSprites.push_back(al_load_bitmap("./assets/regina.png"));
    _pizzaSprites.push_back(al_load_bitmap("./assets/margarita.png"));
    _pizzaSprites.push_back(al_load_bitmap("./assets/americana.png"));
    _pizzaSprites.push_back(al_load_bitmap("./assets/fantasia.png"));

}

Graphic::~Graphic()
{
    al_destroy_display(_display);
    al_destroy_font(_font_Title);
    al_destroy_event_queue(q);
}

void Graphic::start()
{
    this->draw();
}

void Graphic::draw_quantity()
{
    if (_side == 2) {
        al_draw_filled_rectangle(1450, 340, 1650, 390, al_map_rgb(255, 255, 255));
    } else 
        al_draw_filled_rectangle(1450, 340, 1650, 390, al_map_rgb(120, 120, 120));
    al_draw_text(_font, al_map_rgb(0, 0, 0), 1250, 350, 0, "Quantité =     X");
    al_draw_text(_font, al_map_rgb(0, 0, 0), 1500, 350, 0, _chooseQuantity.c_str());
}

void Graphic::draw_pizza_size()
{
    for (int a = 0, x1 = 840, x2 = 900; a < 5; a++, x1 += 70, x2 = x1 + 60) {
        if (a == _chooseSize)
            al_draw_filled_rectangle(x1, 340, x2, 390, al_map_rgb(255,255,255));
        else
            al_draw_filled_rectangle(x1, 340, x2, 390, al_map_rgb(120, 120, 120));
    }

    al_draw_text(_font, al_map_rgb(0, 0, 0), 860, 350, 0, "S");
    al_draw_text(_font, al_map_rgb(0, 0, 0), 925, 350, 0, "M");
    al_draw_text(_font, al_map_rgb(0, 0, 0), 1000, 350, 0, "L");
    al_draw_text(_font, al_map_rgb(0, 0, 0), 1060, 350, 0, "XL");
    al_draw_text(_font, al_map_rgb(0, 0, 0), 1122, 350, 0, "XXL");

    al_draw_line(1200, 300, 1200, 400, al_map_rgb(0, 0, 0), 0);
}

void Graphic::setInputPizza()
{
    if (_choosePizza == 0)
        _pizzaInput = "Regina "; 
    switch (_choosePizza) {

        case 1:
            _pizzaInput = "Margarita ";
            break;
        case 2:
            _pizzaInput = "Americana ";
            break;
        case 3:
            _pizzaInput = "Fantasia ";
            break;
        default:
            break;
    }
    if (_chooseSize == 0)
        _pizzaInput += "S x";
    switch (_chooseSize) {
    case 1:
        _pizzaInput += "M x";
        break;
    case 2:
        _pizzaInput += "L x";
        break;
    case 3:
        _pizzaInput += "XL x";
        break;
    case 4:
        _pizzaInput += "XXL x";
        break;
    default:
        break;
    }
    _pizzaInput += _chooseQuantity.empty() ? "0" : _chooseQuantity;
    _recep.setInput(_pizzaInput);
    _pizzaInput.clear();
    _side = 0;
    _chooseSize = -1;
    _chooseQuantity = "";
    _choosePizza = 0;
}

void Graphic::getPizzaInput()
{

    al_get_keyboard_state(&_key);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    if (al_key_down(&_key, ALLEGRO_KEY_ESCAPE)) {
        _recep.getPipe().KillAll();
        exit(0);
    } else if (al_key_down(&_key, ALLEGRO_KEY_LEFT) && _keyDown == true) {
        if (_side == 0) {
            _choosePizza - 1 < 0 ? _choosePizza = 0 : _choosePizza--;
        } else if (_side == 1) {
            _chooseSize - 1 < 0 ? _chooseSize = 0 : _chooseSize--;
        }
    } else if (al_key_down(&_key, ALLEGRO_KEY_RIGHT) && _keyDown == true) {
        if (_side == 0) {
            _choosePizza + 1 > 3 ? _choosePizza = 3 : _choosePizza ++;
        } else if (_side == 1) {
            _chooseSize + 1 > 4 ? _chooseSize = 4 : _chooseSize ++;
        }
    } else if(al_key_down(&_key, ALLEGRO_KEY_ENTER) && _keyDown == true) {
        if (_side + 1 == 1) {
            _chooseSize = 0;
            _side ++;
        } else if (_side + 1 == 3) {
            setInputPizza();
        } else {
            _side ++;
        }
    }
}

void Graphic::setKeyDown()
{
    al_wait_for_event_timed(q, &evt, 1.0/10);
    if (evt.type == ALLEGRO_EVENT_KEY_DOWN) {
        _keyDown = true;
    } else if (evt.type == ALLEGRO_EVENT_KEY_UP) {
        _keyDown = false;
    }
    if ((evt.type == ALLEGRO_EVENT_KEY_CHAR && evt.keyboard.unichar != 8 && isdigit(evt.keyboard.unichar)) && _side == 2) {
        _chooseQuantity += evt.keyboard.unichar;
    } else if (evt.type == ALLEGRO_EVENT_KEY_CHAR && evt.keyboard.unichar == 8 && _chooseQuantity.size() && _side == 2) {
        _chooseQuantity.pop_back();
    }
}

bool Graphic::getSendState() const
{
    return this->_isSend;
}

void Graphic::draw()
{
    _recep.addKitchen();
    while (1) {
        al_clear_to_color(al_map_rgb(255,153,0));
        al_draw_text(_font_Title, al_map_rgb(0, 0, 0), (1970 / 3) + 150 , 0, 0, "La Plazza");
        for (int a = 0; a < _pizzaSprites.size(); a += 1) {
            if (_choosePizza == a)
                al_draw_filled_rectangle((((1920 / 4) - 300) + a * (al_get_bitmap_width(_pizzaSprites[a]) + 130)), 50, (((1920 / 4) - 200) + a * (al_get_bitmap_width(_pizzaSprites[a]) + 130) + 100), 280, al_map_rgb(255, 255, 255));
            else
                al_draw_filled_rectangle((((1920 / 4) - 300) + a * (al_get_bitmap_width(_pizzaSprites[a]) + 130)), 50, (((1920 / 4) - 200) + a * (al_get_bitmap_width(_pizzaSprites[a]) + 130) + 100), 280, al_map_rgb(120,120,120));
            al_draw_bitmap(_pizzaSprites[a], ((1920 / 4) - 350) + a * (al_get_bitmap_width(_pizzaSprites[a]) + 130), 50, 0);
        }
        draw_pizza_size();
        draw_quantity();
        al_draw_line(0, 400, 1920, 400, al_map_rgb(0, 0, 0), 0);
        al_get_keyboard_state(&_key);
        if (al_key_down(&_key, ALLEGRO_KEY_ESCAPE)) {
            _recep.getPipe().KillAll();
            exit(0);
        }
        setKeyDown();
        getPizzaInput();
        this->drawCook();
        if (_isSend)
            _recep.start();
        al_flip_display();
    }
}

void Graphic::drawCook()
{
    int yPos = 0;
    int count = 0;

    for (int a = 0, count = 0; a < _recep.getKitchens().size(); a += 1, count++) {
        if ((count * 650 + 610) > 1910) {
            yPos += 120;
            count = 0;
        }
            al_draw_filled_rectangle(count * 650 + 30,  450 + yPos, count * 650 + 610, 540 + yPos, al_map_rgb(120,120,120));
        for (int b = 0; b < _recep.getKitchens()[a].size(); b += 1) {
            if (_recep.getKitchens()[a][b]->isAvailable())
                al_draw_filled_circle((count * 650 + ((b+1)*70)), 500 + yPos, 30, al_map_rgb(0, 255, 0));
            else
                al_draw_filled_circle((count * 650 + ((b+1)*70)), 500 + yPos, 30, al_map_rgb(255, 0, 0));
        }
    }
}