/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Event
*/

#ifndef EVENT_HPP_
#define EVENT_HPP_

#include "../../libs/include/irrlicht.h"
#include <iostream>
#include <vector>

namespace Evt {
    enum Type {
        GUI_ID_PLAY_BUTTON = 101,
        GUI_ID_LAUNCH_BUTTON,
        GUI_ID_PLAYER1_BUTTON,
        GUI_ID_PLAYER2_BUTTON,
        GUI_ID_PLAYER3_BUTTON,
        GUI_ID_PLAYER4_BUTTON,
        GUI_ID_OPTION_BUTTON,
        GUI_ID_QUIT_BUTTON,
        GUI_ID_SAVE_BUTTON,
        GUI_ID_LOAD_BUTTON,
        GUI_ID_MAP_BUTTON,
        GUI_ID_RESUME_BUTTON,
        GUI_ID_PAUSE_QUIT_BUTTON,
        GUI_ID_OPTION_QUIT_BUTTON,
        GUI_COUNT = 255,
    };
};

class Event : public irr::IEventReceiver
{
    public:
        Event();
        ~Event();
        virtual bool OnEvent(const irr::SEvent& event);
        virtual bool IsKeyDown(irr::EKEY_CODE keyCode);
        bool IsButtonDown(Evt::Type ButtonCode);
        void releaseKey(irr::EKEY_CODE keyCode);

    private:
        std::vector<bool> KeyIsDown;
        std::vector<bool> ButtonIsDown;
};

#endif /* !EVENT_HPP_ */
