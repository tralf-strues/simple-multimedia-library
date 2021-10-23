//------------------------------------------------------------------------------
//! @author Nikita Mochalov (github.com/tralf-strues)
//! @file listener_notifier.h
//! @date 2021-10-04
//! 
//! @copyright Copyright (c) 2021
//------------------------------------------------------------------------------

#ifndef LISTENER_NOTIFIER_H
#define LISTENER_NOTIFIER_H

#include "../sml_containers.h"
#include "event.h"

static const size_t MAX_LISTENED_EVENTS = 3;

class Listener
{
public:
    virtual void onEvent(const Event& event) = 0;
};

class Notifier
{
public:
    virtual void attachListener(const std::initializer_list<EventType>& types, Listener* listener);
    virtual void detachListener(Listener* listener);

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

    List<ListenerInfo> m_Listeners;

    virtual void notify(const Event& event);
};

#endif // LISTENER_NOTIFIER_H