
/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Menu
*/

#include "../include/System/Menu.hpp"

Menu::Menu(irr::IrrlichtDevice *window)
{
    this->_state = -1;
    this->_window = window;
    this->driver = this->_window->getVideoDriver();
    this->env = this->_window->getGUIEnvironment();
    this->skin = this->env->getSkin();
    this->font = this->env->getFont("./Assets/TTF/Bubblegum.ttf");
    this->scene = this->_window->getSceneManager()->createNewSceneManager(false);
    this->scene->getParameters()->setAttribute(irr::scene::COLLADA_CREATE_SCENE_INSTANCES, true);
    this->subscene = this->_window->getSceneManager()->createNewSceneManager(false);
    this->subscene->getParameters()->setAttribute(irr::scene::COLLADA_CREATE_SCENE_INSTANCES, true);
    this->menu = this->env->addMenu();
    for (size_t idx = 0; idx < 4; idx++)
        this->players.push_back({false, NULL, NULL});
    if (font) {
        this->skin->setFont(font);
    }
}

Menu::~Menu()
{
}

irr::scene::ISceneManager *Menu::getSceneManager() const 
{
    return this->scene;
}

std::vector<bool> Menu::getBot()
{
    std::vector<bool> bot;

    for (size_t idx = 0; idx < this->players.size(); idx++) {
        bot.push_back(std::get<bool>(this->players[idx]));
    }
    return bot;
}

void Menu::SwapBot(int index)
{
    int total = 0;

    for (size_t idx = 0; idx < this->players.size(); idx++)
        total += (std::get<bool>(this->players[idx])) ? 1 : 0;
    if (total >= 2 && !std::get<bool>(this->players[index]))
        return;
    std::get<bool>(this->players[index]) = !std::get<bool>(this->players[index]);
    if (index == 0) {
        if (std::get<bool>(this->players[index])) {
            std::get<irr::gui::IGUIButton *>(this->players[index])->setImage(this->driver->getTexture("./Assets/Texture/Player_selec.png"));
            std::get<irr::gui::IGUIImage *>(this->players[index])->setImage(this->driver->getTexture("./Assets/Texture/Player_1.png"));
        } else {
            std::get<irr::gui::IGUIButton *>(this->players[index])->setImage(this->driver->getTexture("./Assets/Texture/Bot_selec.png"));
            std::get<irr::gui::IGUIImage *>(this->players[index])->setImage(this->driver->getTexture("./Assets/Texture/Bot_1.png"));
        }
    } else if (index == 1) {
        if (std::get<bool>(this->players[index])) {
            std::get<irr::gui::IGUIButton *>(this->players[index])->setImage(this->driver->getTexture("./Assets/Texture/Player_selec.png"));
            std::get<irr::gui::IGUIImage *>(this->players[index])->setImage(this->driver->getTexture("./Assets/Texture/Player_2.png"));
        } else {
            std::get<irr::gui::IGUIButton *>(this->players[index])->setImage(this->driver->getTexture("./Assets/Texture/Bot_selec.png"));
            std::get<irr::gui::IGUIImage *>(this->players[index])->setImage(this->driver->getTexture("./Assets/Texture/Bot_2.png"));
        }
    } else if (index == 2) {
        if (std::get<bool>(this->players[index])) {
            std::get<irr::gui::IGUIButton *>(this->players[index])->setImage(this->driver->getTexture("./Assets/Texture/Player_selec.png"));
            std::get<irr::gui::IGUIImage *>(this->players[index])->setImage(this->driver->getTexture("./Assets/Texture/Player_3.png"));
        } else {
            std::get<irr::gui::IGUIButton *>(this->players[index])->setImage(this->driver->getTexture("./Assets/Texture/Bot_selec.png"));
            std::get<irr::gui::IGUIImage *>(this->players[index])->setImage(this->driver->getTexture("./Assets/Texture/Bot_3.png"));
        }
    } else if (index == 3) {
        if (std::get<bool>(this->players[index])) {
            std::get<irr::gui::IGUIButton *>(this->players[index])->setImage(this->driver->getTexture("./Assets/Texture/Player_selec.png"));
            std::get<irr::gui::IGUIImage *>(this->players[index])->setImage(this->driver->getTexture("./Assets/Texture/Player_4.png"));
        } else {
            std::get<irr::gui::IGUIButton *>(this->players[index])->setImage(this->driver->getTexture("./Assets/Texture/Bot_selec.png"));
            std::get<irr::gui::IGUIImage *>(this->players[index])->setImage(this->driver->getTexture("./Assets/Texture/Bot_4.png"));
        }
    }
}

void Menu::SwitchMenu(int state)
{
    irr::gui::IGUIButton *tmp;

    if (this->_state != state && state == 0) {
        this->_state = state;
        this->env->clear();
        tmp = this->env->addButton(irr::core::rect<irr::s32>(760, 200, 1140 , 300), 0, Evt::GUI_ID_PLAY_BUTTON);
        tmp->setImage(this->driver->getTexture("./Assets/Texture/long_bar_play.png"));
        tmp->setUseAlphaChannel(true);
        tmp->setDrawBorder(false);
        tmp = this->env->addButton(irr::core::rect<irr::s32>(760,450,1140,550), 0, Evt::GUI_ID_OPTION_BUTTON);
        tmp->setImage(this->driver->getTexture("./Assets/Texture/long_bar_option.png"));
        tmp->setUseAlphaChannel(true);
        tmp->setDrawBorder(false);
        tmp = this->env->addButton(irr::core::rect<irr::s32>(760,700,1140,800), 0, Evt::GUI_ID_QUIT_BUTTON);
        tmp->setImage(this->driver->getTexture("./Assets/Texture/long_bar_quit.png"));
        tmp->setUseAlphaChannel(true);
        tmp->setDrawBorder(false);
    } else if (this->_state != state && state == 3) {
        this->_state = state;
        this->env->clear();
        tmp = this->env->addButton(irr::core::rect<irr::s32>(760,150,1140,250), 0, Evt::GUI_ID_RESUME_BUTTON);
        tmp->setImage(this->driver->getTexture("./Assets/Texture/long_bar_resume.png"));
        tmp->setUseAlphaChannel(true);
        tmp->setDrawBorder(false);
        tmp = this->env->addButton(irr::core::rect<irr::s32>(760,400,1140,500), 0, Evt::GUI_ID_SAVE_BUTTON);
        tmp->setImage(this->driver->getTexture("./Assets/Texture/long_bar_save.png"));
        tmp->setUseAlphaChannel(true);
        tmp->setDrawBorder(false);
        tmp = this->env->addButton(irr::core::rect<irr::s32>(760,650,1140,750), 0, Evt::GUI_ID_PAUSE_QUIT_BUTTON);
        tmp->setImage(this->driver->getTexture("./Assets/Texture/long_bar_back.png"));
        tmp->setUseAlphaChannel(true);
        tmp->setDrawBorder(false);
    } else if (this->_state != state && state == 2) {
        this->_state = state;
        this->env->clear();
        tmp = this->env->addButton(irr::core::rect<irr::s32>(760,200,1140,300), 0, Evt::GUI_ID_MAP_BUTTON);
        tmp->setImage(this->driver->getTexture("./Assets/Texture/long_bar_newmap.png"));
        tmp->setUseAlphaChannel(true);
        tmp->setDrawBorder(false);
        tmp = this->env->addButton(irr::core::rect<irr::s32>(760,400,1140,500), 0, Evt::GUI_ID_SAVE_BUTTON);
        tmp->setImage(this->driver->getTexture("./Assets/Texture/long_bar_save.png"));
        tmp->setUseAlphaChannel(true);
        tmp->setDrawBorder(false);
        tmp = this->env->addButton(irr::core::rect<irr::s32>(760,600,1140,700), 0, Evt::GUI_ID_LOAD_BUTTON);
        tmp->setImage(this->driver->getTexture("./Assets/Texture/long_bar_load.png"));
        tmp->setUseAlphaChannel(true);
        tmp->setDrawBorder(false);
        tmp = this->env->addButton(irr::core::rect<irr::s32>(760,800,1140,900), 0, Evt::GUI_ID_OPTION_QUIT_BUTTON);
        tmp->setImage(this->driver->getTexture("./Assets/Texture/long_bar_quit.png"));
        tmp->setUseAlphaChannel(true);
        tmp->setDrawBorder(false);
    } else if (this->_state != state && state == 4) {
        this->_state = state;
        this->env->clear();
        tmp = this->env->addButton(irr::core::rect<irr::s32>(760,850,1140,950), 0, Evt::GUI_ID_LAUNCH_BUTTON);
        tmp->setImage(this->driver->getTexture("./Assets/Texture/long_bar_play.png"));
        tmp->setUseAlphaChannel(true);
        tmp->setDrawBorder(false);
        std::get<irr::gui::IGUIButton *>(this->players[0]) = this->env->addButton(irr::core::rect<irr::s32>(64,200,464,350), 0, Evt::GUI_ID_PLAYER1_BUTTON);
        if (std::get<bool>(this->players[0])) {
            std::get<irr::gui::IGUIButton *>(this->players[0])->setImage(this->driver->getTexture("./Assets/Texture/Player_selec.png"));
            std::get<irr::gui::IGUIImage *>(this->players[0]) = this->env->addImage(this->driver->getTexture("./Assets/Texture/Player_1.png"), irr::core::vector2di(64, 400), true);
        } else {
            std::get<irr::gui::IGUIButton *>(this->players[0])->setImage(this->driver->getTexture("./Assets/Texture/Bot_selec.png"));
            std::get<irr::gui::IGUIImage *>(this->players[0]) = this->env->addImage(this->driver->getTexture("./Assets/Texture/Bot_1.png"), irr::core::vector2di(64, 400), true);
        }
        std::get<irr::gui::IGUIButton *>(this->players[0])->setUseAlphaChannel(true);
        std::get<irr::gui::IGUIButton *>(this->players[0])->setDrawBorder(false);
        std::get<irr::gui::IGUIButton *>(this->players[1]) = this->env->addButton(irr::core::rect<irr::s32>(528,200,928,350), 0, Evt::GUI_ID_PLAYER2_BUTTON);
        if (std::get<bool>(this->players[1])) {
            std::get<irr::gui::IGUIButton *>(this->players[1])->setImage(this->driver->getTexture("./Assets/Texture/Player_selec.png"));
            std::get<irr::gui::IGUIImage *>(this->players[1]) = this->env->addImage(this->driver->getTexture("./Assets/Texture/Player_2.png"), irr::core::vector2di(528, 400), true);
        } else {
            std::get<irr::gui::IGUIButton *>(this->players[1])->setImage(this->driver->getTexture("./Assets/Texture/Bot_selec.png"));
            std::get<irr::gui::IGUIImage *>(this->players[1]) = this->env->addImage(this->driver->getTexture("./Assets/Texture/Bot_2.png"), irr::core::vector2di(528, 400), true);
        }
        std::get<irr::gui::IGUIButton *>(this->players[1])->setUseAlphaChannel(true);
        std::get<irr::gui::IGUIButton *>(this->players[1])->setDrawBorder(false);
        std::get<irr::gui::IGUIButton *>(this->players[2]) = this->env->addButton(irr::core::rect<irr::s32>(992,200,1392,350), 0, Evt::GUI_ID_PLAYER3_BUTTON);
        if (std::get<bool>(this->players[2])) {
            std::get<irr::gui::IGUIButton *>(this->players[2])->setImage(this->driver->getTexture("./Assets/Texture/Player_selec.png"));
            std::get<irr::gui::IGUIImage *>(this->players[2]) = this->env->addImage(this->driver->getTexture("./Assets/Texture/Player_3.png"), irr::core::vector2di(992, 400), true);
        } else {
            std::get<irr::gui::IGUIButton *>(this->players[2])->setImage(this->driver->getTexture("./Assets/Texture/Bot_selec.png"));
            std::get<irr::gui::IGUIImage *>(this->players[2]) = this->env->addImage(this->driver->getTexture("./Assets/Texture/Bot_3.png"), irr::core::vector2di(992, 400), true);
        }
        std::get<irr::gui::IGUIButton *>(this->players[2])->setUseAlphaChannel(true);
        std::get<irr::gui::IGUIButton *>(this->players[2])->setDrawBorder(false);
        std::get<irr::gui::IGUIButton *>(this->players[3]) = this->env->addButton(irr::core::rect<irr::s32>(1456,200,1856,350), 0, Evt::GUI_ID_PLAYER4_BUTTON);
        if (std::get<bool>(this->players[3])) {
            std::get<irr::gui::IGUIButton *>(this->players[3])->setImage(this->driver->getTexture("./Assets/Texture/Player_selec.png"));
            std::get<irr::gui::IGUIImage *>(this->players[3]) = this->env->addImage(this->driver->getTexture("./Assets/Texture/Player_4.png"), irr::core::vector2di(1456, 400), true);
        } else {
            std::get<irr::gui::IGUIButton *>(this->players[3])->setImage(this->driver->getTexture("./Assets/Texture/Bot_selec.png"));
            std::get<irr::gui::IGUIImage *>(this->players[3]) = this->env->addImage(this->driver->getTexture("./Assets/Texture/Bot_4.png"), irr::core::vector2di(1456, 400), true);
        }
        std::get<irr::gui::IGUIButton *>(this->players[3])->setUseAlphaChannel(true);
        std::get<irr::gui::IGUIButton *>(this->players[3])->setDrawBorder(false);
    }
}

