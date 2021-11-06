/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file event.h
 * @date 2021-10-03
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include <inttypes.h>
#include "scancode.h"

namespace Sml
{
    using EventType     = uint32_t;
    using EventCategory = uint64_t; ///< Supposed to be used as a bit-mask.

    const EventType     INVALID_EVENT_TYPE = 0;
    const EventCategory EVENT_CATEGORY_ANY = 0;

    #define DEFINE_STATIC_EVENT_TYPE(type) \
        static constexpr EventType getStaticType() { return type; }
    
    #define DEFINE_STATIC_EVENT_CATEGORY(category) \
        static constexpr EventCategory getStaticCategory() { return category; }

    class EventTarget;

    class Event
    {
    public:
        Event(EventType type = INVALID_EVENT_TYPE, EventCategory category = 0, EventTarget* target = nullptr)
            : m_Type(type), m_Category(category), m_Target(target) {}

        void setType(EventType type) { m_Type = type; }
        void setCategory(EventCategory category) { m_Category = category; }

        EventType getType() const { return m_Type; }
        EventCategory getCategory() const { return m_Category; }

        bool isInCategory(EventCategory category) { return category == (category & m_Category); }

        void setTarget(EventTarget* target) { m_Target = target; }
        EventTarget* getTarget() const { return m_Target; }

        bool isConsumed() const
        {
            return m_Consumed;
        }

        void consume()
        {
            m_Consumed = true;
        }

    protected:
        EventType     m_Type     = INVALID_EVENT_TYPE;
        EventCategory m_Category = 0;

        EventTarget*  m_Target   = nullptr;
        bool          m_Consumed = false;
    };
}
