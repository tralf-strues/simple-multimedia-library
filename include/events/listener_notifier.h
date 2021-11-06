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
        virtual void detachListener(Listener* listener);
        virtual void notify(Event* event);

    protected:
        struct ListenerInfo
        {
            EventType types[MAX_LISTENED_EVENTS];
            Listener* listener;

            ListenerInfo(Listener* listener = nullptr) : listener(listener)
            {
                for (size_t i = 0; i < MAX_LISTENED_EVENTS; ++i)
                {
                    this->types[i] = INVALID_EVENT_TYPE;
                }
            }

            ListenerInfo(const std::initializer_list<EventType>& types, 
                        Listener* listener = nullptr)
                : ListenerInfo(listener) 
            {
                assert(types.size() <= MAX_LISTENED_EVENTS);

                auto initIt = types.begin();
                for (size_t i = 0; initIt != types.end(); ++initIt, ++i)
                {
                    this->types[i] = *initIt;
                }
            }
        };

        std::list<ListenerInfo> m_Listeners;
    };
}
