/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file mouse.h
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include "SDL.h"
#include "../math/vec2.h"
#include "../utils/bit.h"

namespace Sml
{
    enum class MouseButton
    {
        LEFT   = BIT(0),
        MIDDLE = BIT(1),
        RIGHT  = BIT(2)
    };

    class MouseButtonsState
    {
    public:
        bool isButtonDown(MouseButton button) const;
        void setButton(MouseButton button);
        void resetButton(MouseButton button);

    private:
        uint8_t m_PressedButtons = 0;
    };

    struct MouseState
    {
        Vec2<int32_t>     pos            = {0, 0};
        MouseButtonsState pressedButtons = {};

        static MouseState getMouseState();
    };
}