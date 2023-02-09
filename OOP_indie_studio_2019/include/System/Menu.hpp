/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "../../libs/include/irrlicht.h"
#include "./Event.hpp"
#include <iostream>
#include <tuple>

class Menu {
    public:
        Menu(irr::IrrlichtDevice *_window);
        ~Menu();
        void SwitchMenu(int state);
        void SwapBot(int index);
        std::vector<bool> getBot();
        void displayMenu();
        void displaySubmenu();
        void displayPausemenu();
        irr::scene::ISceneManager *getSceneManager() const;
    protected:
    private:
        int _state;
        std::vector<std::tuple<bool, irr::gui::IGUIButton *, irr::gui::IGUIImage *> > players;
        irr::video::IVideoDriver *driver;
        irr::gui::IGUIContextMenu *menu;
        irr::gui::IGUIContextMenu *submenu;
        irr::gui::IGUIContextMenu *pausemenu;
        irr::gui::IGUIContextMenu *selectmenu;
        irr::gui::IGUIEnvironment *env;
        irr::IrrlichtDevice *_window;
        irr::gui::IGUISkin *skin;
        irr::gui::IGUIFont *font;
        irr::scene::ISceneManager *pausescene;
        irr::scene::ISceneManager *subscene;
        irr::scene::ISceneManager *scene;
        irr::scene::ISceneManager *select;
};

#endif /* !MENU_HPP_ */
