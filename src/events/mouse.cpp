/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file mouse.cpp
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 */

#include "events/mouse.h"

namespace Sml
{
    MouseButton convertNativeButton(uint8_t nativeButton)
    {
        switch (nativeButton)
        {
            case SDL_BUTTON_LEFT:   { return MouseButton::LEFT;    }
            case SDL_BUTTON_MIDDLE: { return MouseButton::MIDDLE;  }
            case SDL_BUTTON_RIGHT:  { return MouseButton::RIGHT;   }
            default:                { return MouseButton::INVALID; }
        }
    }

    bool MouseButtonsState::isButtonDown(MouseButton button) const
    { 
        return (m_PressedButtons & static_cast<uint8_t>(button)) != 0;
    }

    void MouseButtonsState::setButton(MouseButton button)
    {
        m_PressedButtons |= static_cast<uint8_t>(button);
    }

    void MouseButtonsState::resetButton(MouseButton button)
    {
        m_PressedButtons &= ~(static_cast<uint8_t>(button));
    }

    MouseState::MouseState(int32_t x, int32_t y) : x(x), y(y) {}

    MouseState MouseState::getMouseState()
    {
        MouseState mouseState = {};
        uint32_t buttons = SDL_GetMouseState(&mouseState.x, &mouseState.y);

        if ((buttons & SDL_BUTTON_LMASK) != 0)
        {
            mouseState.pressedButtons.setButton(MouseButton::LEFT);
        }

        if ((buttons & SDL_BUTTON_MMASK) != 0)
        {
            mouseState.pressedButtons.setButton(MouseButton::MIDDLE);
        }

        if ((buttons & SDL_BUTTON_RMASK) != 0)
        {
            mouseState.pressedButtons.setButton(MouseButton::RIGHT);
        }

        return mouseState;
    }
}