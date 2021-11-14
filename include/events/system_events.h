/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file system_events.h
 * @date 2021-10-21
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include "event.h"
#include "mouse.h"
#include "../utils/bit.h"

namespace Sml
{
    enum SystemEventType
    {
        /* Window events */
        WINDOW_CLOSE = 1,

        /* Mouse events */
        MOUSE_MOVED,
        MOUSE_BUTTON_PRESSED,
        MOUSE_BUTTON_RELEASED,

        /* Keyboard events */
        KEY_PRESSED,
        KEY_RELEASED,

        /* Other */
        // PROPERTY_CHANGE,

        /** Custom event types must not be less than this. */
        SML_EVENT_TYPE_FIRST_UNSPECIFIED = 4096
    };

    enum SystemEventCategory
    {
        EVENT_CATEGORY_WINDOW       = BIT(0),

        EVENT_CATEGORY_INPUT        = BIT(1),
        EVENT_CATEGORY_MOUSE        = BIT(2),
        EVENT_CATEGORY_MOUSE_BUTTON = BIT(3),
        EVENT_CATEGORY_KEYBOARD     = BIT(4),

        /** Custom event categories must not be less than this. */
        SML_EVENT_CATEGORY_FIRST_UNSPECIFIED = BIT(8)
    };

    //------------------------------------------------------------------------------
    // Event category [WINDOW]
    //------------------------------------------------------------------------------
    class WindowEvent : public Event
    {
    public:
        WindowEvent(EventTarget* target = nullptr)
            : Event(getStaticType(), getStaticCategory(), target) {}

        DEFINE_STATIC_EVENT_TYPE(INVALID_EVENT_TYPE)
        DEFINE_STATIC_EVENT_CATEGORY(EVENT_CATEGORY_WINDOW)
    };

    class WindowCloseEvent : public WindowEvent
    {
    public:
        WindowCloseEvent(EventTarget* target = nullptr) : WindowEvent(target)
        {
            m_Type = getStaticType();
            m_Category = getStaticCategory();
        }

        DEFINE_STATIC_EVENT_TYPE(WINDOW_CLOSE)
        DEFINE_STATIC_EVENT_CATEGORY(WindowEvent::getStaticCategory())
    };

    //------------------------------------------------------------------------------
    // Event category [INPUT->MOUSE]
    //------------------------------------------------------------------------------
    class MouseEvent : public Event
    {
    public:
        MouseEvent(int32_t x = 0, int32_t y = 0, EventTarget* target = nullptr)
            : Event(getStaticType(), getStaticCategory(), target), m_X(x), m_Y(y) {}

        void setX(int32_t x) { m_X = x; }
        void setY(int32_t y) { m_Y = y; }

        int32_t getX() const { return m_X; }
        int32_t getY() const { return m_Y; }

        DEFINE_STATIC_EVENT_TYPE(INVALID_EVENT_TYPE)
        DEFINE_STATIC_EVENT_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_MOUSE)

    protected:
        int32_t m_X;
        int32_t m_Y;
    };

    class MouseMovedEvent : public MouseEvent
    {
    public:
        MouseMovedEvent(int32_t x = 0, int32_t y = 0,
                        int32_t deltaX = 0, int32_t deltaY = 0,
                        EventTarget* target = nullptr)
            : MouseEvent(x, y, target), m_DeltaX(deltaX), m_DeltaY(deltaY)
        {
            m_Type = getStaticType();
            m_Category = getStaticCategory();
        }

        void setDeltaX(int32_t deltaX) { m_DeltaX = deltaX; }
        void setDeltaY(int32_t deltaY) { m_DeltaY = deltaY; }

        int32_t getDeltaX() const { return m_DeltaX; }
        int32_t getDeltaY() const { return m_DeltaY; }

        DEFINE_STATIC_EVENT_TYPE(MOUSE_MOVED)
        DEFINE_STATIC_EVENT_CATEGORY(MouseEvent::getStaticCategory())

    private:
        int32_t m_DeltaX;
        int32_t m_DeltaY;
    };

    //------------------------------------------------------------------------------
    // Event category [INPUT->MOUSE->MOUSE_BUTTON]
    //------------------------------------------------------------------------------
    class MouseButtonEvent : public MouseEvent
    {
    public:
        MouseButtonEvent(int32_t x = 0, int32_t y = 0,
                         MouseButton button = MouseButton::INVALID,
                         EventTarget* target = nullptr)
            : MouseEvent(x, y, target), m_Button(button)
        {
            m_Type = getStaticType();
            m_Category = getStaticCategory();
        }

        DEFINE_STATIC_EVENT_TYPE(INVALID_EVENT_TYPE)
        DEFINE_STATIC_EVENT_CATEGORY(MouseEvent::getStaticCategory() | EVENT_CATEGORY_MOUSE_BUTTON)
    
    protected:
        MouseButton m_Button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int32_t x = 0, int32_t y = 0,
                                MouseButton button = MouseButton::INVALID,
                                EventTarget* target = nullptr)
            : MouseButtonEvent(x, y, button, target)
        {
            m_Type = getStaticType();
            m_Category = getStaticCategory();
        }

        DEFINE_STATIC_EVENT_TYPE(MOUSE_BUTTON_PRESSED)
        DEFINE_STATIC_EVENT_CATEGORY(MouseButtonEvent::getStaticCategory())
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int32_t x = 0, int32_t y = 0,
                                 MouseButton button = MouseButton::INVALID,
                                 EventTarget* target = nullptr)
            : MouseButtonEvent(x, y, button, target)
        {
            m_Type = getStaticType();
            m_Category = getStaticCategory();
        }

        DEFINE_STATIC_EVENT_TYPE(MOUSE_BUTTON_RELEASED)
        DEFINE_STATIC_EVENT_CATEGORY(MouseButtonEvent::getStaticCategory())
    };

    //------------------------------------------------------------------------------
    // Event category [INPUT->KEYBOARD]
    //------------------------------------------------------------------------------
    class KeyEvent : public Event
    {
    public:
        KeyEvent(Scancode scancode = SCANCODE_INVALID, EventTarget* target = nullptr)
            : Event(getStaticType(), getStaticCategory(), target), m_Scancode(scancode) {}

        void setScancode(Scancode scancode) { m_Scancode = scancode; }
        Scancode getScancode() const { return m_Scancode; }

        DEFINE_STATIC_EVENT_TYPE(INVALID_EVENT_TYPE)
        DEFINE_STATIC_EVENT_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_KEYBOARD)

    protected:
        Scancode m_Scancode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(Scancode scancode = SCANCODE_INVALID, EventTarget* target = nullptr)
            : KeyEvent(scancode, target)
        {
            m_Type = getStaticType();
            m_Category = getStaticCategory();
        }

        DEFINE_STATIC_EVENT_TYPE(KEY_PRESSED)
        DEFINE_STATIC_EVENT_CATEGORY(KeyEvent::getStaticCategory())
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(Scancode scancode = SCANCODE_INVALID, EventTarget* target = nullptr)
            : KeyEvent(scancode, target)
        {
            m_Type = getStaticType();
            m_Category = getStaticCategory();
        }

        DEFINE_STATIC_EVENT_TYPE(KEY_RELEASED)
        DEFINE_STATIC_EVENT_CATEGORY(KeyEvent::getStaticCategory())
    };
}
