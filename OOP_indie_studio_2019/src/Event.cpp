/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Event
*/

#include "../include/System/Event.hpp"

Event::Event()
{
    for (size_t i = 0; i < 255; i += 1) {
        this->KeyIsDown.push_back(false);
        this->ButtonIsDown.push_back(false);
    }
}

Event::~Event()
{
}

bool Event::OnEvent(const irr::SEvent& event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
        this->KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    } else if (event.EventType == irr::EET_GUI_EVENT) {
        irr::s32 id = event.GUIEvent.Caller->getID();
        switch (event.GUIEvent.EventType) {
            case irr::gui::EGET_BUTTON_CLICKED:
                switch (id) {
                    case Evt::GUI_ID_PLAY_BUTTON :
                        this->ButtonIsDown[Evt::GUI_ID_PLAY_BUTTON] = true;
                        return true;
                    case Evt::GUI_ID_OPTION_BUTTON :
                        this->ButtonIsDown[Evt::GUI_ID_OPTION_BUTTON] = true;
                        return true;
                    case Evt::GUI_ID_QUIT_BUTTON :
                        this->ButtonIsDown[Evt::GUI_ID_QUIT_BUTTON] = true;
                        return true;
                    case Evt::GUI_ID_MAP_BUTTON :
                        this->ButtonIsDown[Evt::GUI_ID_MAP_BUTTON] = true;
                        return true;
                    case Evt::GUI_ID_PAUSE_QUIT_BUTTON :
                        this->ButtonIsDown[Evt::GUI_ID_PAUSE_QUIT_BUTTON] = true;
                        return true;
                    case Evt::GUI_ID_RESUME_BUTTON :
                        this->ButtonIsDown[Evt::GUI_ID_RESUME_BUTTON] = true;
                        return true;
                    case Evt::GUI_ID_OPTION_QUIT_BUTTON :
                        this->ButtonIsDown[Evt::GUI_ID_OPTION_QUIT_BUTTON] = true;
                        return true;
                    case Evt::GUI_ID_LAUNCH_BUTTON :
                        this->ButtonIsDown[Evt::GUI_ID_LAUNCH_BUTTON] = true;
                        return true;
                    case Evt::GUI_ID_PLAYER1_BUTTON :
                        this->ButtonIsDown[Evt::GUI_ID_PLAYER1_BUTTON] = true;
                        return true;
                    case Evt::GUI_ID_PLAYER2_BUTTON :
                        this->ButtonIsDown[Evt::GUI_ID_PLAYER2_BUTTON] = true;
                        return true;
                    case Evt::GUI_ID_PLAYER3_BUTTON :
                        this->ButtonIsDown[Evt::GUI_ID_PLAYER3_BUTTON] = true;
                        return true;
                    case Evt::GUI_ID_PLAYER4_BUTTON :
                        this->ButtonIsDown[Evt::GUI_ID_PLAYER4_BUTTON] = true;
                        return true;
                    case Evt::GUI_ID_SAVE_BUTTON :
                        this->ButtonIsDown[Evt::GUI_ID_SAVE_BUTTON] = true;
                        return true;
                    case Evt::GUI_ID_LOAD_BUTTON :
                        this->ButtonIsDown[Evt::GUI_ID_LOAD_BUTTON] = true;
                        return true;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    return false;
}

bool Event::IsKeyDown(irr::EKEY_CODE keyCode)
{
    return this->KeyIsDown[keyCode];
}

void Event::releaseKey(irr::EKEY_CODE keyCode) 
{
    this->KeyIsDown[keyCode] = false;
}

bool Event::IsButtonDown(Evt::Type ButtonCode)
{
    if (this->ButtonIsDown[ButtonCode]) {
        this->ButtonIsDown[ButtonCode] = false;
        return true;
    }
    return false;
}