//------------------------------------------------------------------------------
//! @author Nikita Mochalov (github.com/tralf-strues)
//! @file event.h
//! @date 2021-10-03
//! 
//! @copyright Copyright (c) 2021
//------------------------------------------------------------------------------

#ifndef EVENT_H
#define EVENT_H

#include <inttypes.h>
#include "scancode.h"

using EventType     = uint32_t;
using EventCategory = uint64_t; ///< Supposed to be used as a bit-mask.

const EventType     INVALID_EVENT_TYPE = 0;
const EventCategory EVENT_CATEGORY_ANY = 0;

#define DEFINE_STATIC_EVENT_TYPE(type)         static EventType     getStaticType()     { return type; }
#define DEFINE_STATIC_EVENT_CATEGORY(category) static EventCategory getStaticCategory() { return category; }

struct Event
{
    EventType     type     = INVALID_EVENT_TYPE;
    EventCategory category = 0;
    bool          consumed = false;

    Event(EventType type = INVALID_EVENT_TYPE, EventCategory category = 0)
        : type(type),
          category(category)
    {
    }

    bool isInCategory(EventCategory category)
    {
        return category == (category && this->category);
    }
};

#endif // EVENT_H