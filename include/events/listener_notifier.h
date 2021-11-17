/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file listener_notifier.h
 * @date 2021-10-04
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include <assert.h>
#include <initializer_list>
#include <unordered_map>
#include <list>
#include "event.h"

namespace Sml
{
    static const size_t MAX_LISTENED_EVENTS = 3;

    class Listener
    {
    public:
        virtual ~Listener() = default;
        virtual void onEvent(Event* event) = 0;
    };

    class Notifier
    {
    public:
        ~Notifier(); ///< FIXME: Manage memory smarter!

        virtual void attachListener(const std::initializer_list<EventType>& types, Listener* listener);
        virtual void detachListener(Listener* listener); // FIXME: doesn't free memory of listener
        virtual void notify(Event* event);

    protected:
        std::unordered_map<EventType, std::list<Listener*>*> m_Listeners;
    };
}
