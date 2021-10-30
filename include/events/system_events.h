//------------------------------------------------------------------------------
//! @author Nikita Mochalov (github.com/tralf-strues)
//! @file system_events.h
//! @date 2021-10-21
//! 
//! @copyright Copyright (c) 2021
//------------------------------------------------------------------------------

#ifndef SYSTEM_EVENTS_H
#define SYSTEM_EVENTS_H

#include "event.h"
#include "../utils/bit.h"

enum SystemEventType
{
    /* Window events */
    WINDOW_CLOSE = 1,

    /* Mouse events */
    MOUSE_MOVED,
    MOUSE_BUTTON_PRESSED,

    /* Keyboard events */
    KEY_PRESSED,
    KEY_RELEASED,

    /* Custom event types must not be less than this. */
    SML_EVENT_TYPE_FIRST_UNSPECIFIED = 4096
};

enum SystemEventCategory
{
    EVENT_CATEGORY_WINDOW   = BIT(0),

    EVENT_CATEGORY_INPUT    = BIT(1),
    EVENT_CATEGORY_MOUSE    = BIT(2),
    EVENT_CATEGORY_KEYBOARD = BIT(3),

    /* Custom event categories must not be less than this. */
    SML_EVENT_CATEGORY_FIRST_UNSPECIFIED = BIT(8)
};

//------------------------------------------------------------------------------
// Event category [WINDOW]
//------------------------------------------------------------------------------

class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() : Event(getStaticType(), getStaticCategory()) {}

    DEFINE_STATIC_EVENT_TYPE(WINDOW_CLOSE)
    DEFINE_STATIC_EVENT_CATEGORY(EVENT_CATEGORY_WINDOW)
};

//------------------------------------------------------------------------------
// Event category [MOUSE]
//------------------------------------------------------------------------------

class MouseEvent : public Event
{
public:
    MouseEvent(int32_t x = 0, int32_t y = 0)
        : Event(getStaticType(), getStaticCategory()), m_X(x), m_Y(y) {}

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
    MouseMovedEvent(int32_t x = 0, int32_t y = 0)
        : MouseEvent(x, y)
    {
        m_Type = getStaticType();
        m_Category = getStaticCategory();
    }

    DEFINE_STATIC_EVENT_TYPE(MOUSE_MOVED)
    DEFINE_STATIC_EVENT_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_MOUSE)
};

class MouseButtonPressedEvent : public MouseEvent
{
public:
    MouseButtonPressedEvent(int32_t x = 0, int32_t y = 0)
        : MouseEvent(x, y)
    {
        m_Type = getStaticType();
        m_Category = getStaticCategory();
    }

    DEFINE_STATIC_EVENT_TYPE(MOUSE_BUTTON_PRESSED)
    DEFINE_STATIC_EVENT_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_MOUSE)
};

//------------------------------------------------------------------------------
// Event category [KEYBOARD]
//------------------------------------------------------------------------------

class KeyEvent : public Event
{
public:
    KeyEvent(Scancode scancode = SCANCODE_INVALID)
        : Event(getStaticType(), getStaticCategory()), m_Scancode(scancode) {}

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
    KeyPressedEvent(Scancode scancode = SCANCODE_INVALID) : KeyEvent(scancode)
    {
        m_Type = getStaticType();
        m_Category = getStaticCategory();
    }

    DEFINE_STATIC_EVENT_TYPE(KEY_PRESSED)
    DEFINE_STATIC_EVENT_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_KEYBOARD)
};

class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent(Scancode scancode = SCANCODE_INVALID) : KeyEvent(scancode)
    {
        m_Type = getStaticType();
        m_Category = getStaticCategory();
    }

    DEFINE_STATIC_EVENT_TYPE(KEY_RELEASED)
    DEFINE_STATIC_EVENT_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_KEYBOARD)
};

#endif // SYSTEM_EVENTS_H