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
#include "utils/bit.h"

enum SystemEventType
{
    /* Window events */
    WINDOW_CLOSE,

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

struct WindowCloseEvent : public Event
{
    WindowCloseEvent() : Event(getStaticType(), getStaticCategory()) {}

    DEFINE_STATIC_EVENT_TYPE(WINDOW_CLOSE)
    DEFINE_STATIC_EVENT_CATEGORY(EVENT_CATEGORY_WINDOW)
};

//------------------------------------------------------------------------------
// Event category [MOUSE]
//------------------------------------------------------------------------------

struct MouseMovedEvent : public Event
{
    int32_t x;
    int32_t y;

    MouseMovedEvent(int32_t x = 0, int32_t y = 0) : Event(getStaticType(), getStaticCategory()), x(x), y(y)
    {
    }

    DEFINE_STATIC_EVENT_TYPE(MOUSE_MOVED)
    DEFINE_STATIC_EVENT_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_MOUSE)
};

//------------------------------------------------------------------------------
// Event category [KEYBOARD]
//------------------------------------------------------------------------------

struct KeyEvent : public Event
{
    Scancode scancode;

    KeyEvent(Scancode scancode = SCANCODE_INVALID)
        : Event(getStaticType(), getStaticCategory()), scancode(scancode)
    {
    }

    DEFINE_STATIC_EVENT_TYPE(INVALID_EVENT_TYPE)
    DEFINE_STATIC_EVENT_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_KEYBOARD)
};

struct KeyPressedEvent : public KeyEvent
{
    KeyPressedEvent(Scancode scancode = SCANCODE_INVALID) : KeyEvent(scancode)
    {
    }

    DEFINE_STATIC_EVENT_TYPE(KEY_PRESSED)
    DEFINE_STATIC_EVENT_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_KEYBOARD)
};

struct KeyReleasedEvent : public KeyEvent
{
    KeyReleasedEvent(Scancode scancode = SCANCODE_INVALID) : KeyEvent(scancode)
    {
    }

    DEFINE_STATIC_EVENT_TYPE(KEY_RELEASED)
    DEFINE_STATIC_EVENT_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_KEYBOARD)
};

#endif // SYSTEM_EVENTS_H