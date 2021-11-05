//------------------------------------------------------------------------------
//! @author Nikita Mochalov (github.com/tralf-strues)
//! @file listener_notifier.cpp
//! @date 2021-10-04
//! 
//! @copyright Copyright (c) 2021
//------------------------------------------------------------------------------

#include "events/listener_notifier.h"

namespace Sml
{

Notifier::~Notifier()
{
    for (auto listenerInfo : m_Listeners)
    {
        delete listenerInfo.listener;
    }
}

void Notifier::attachListener(const std::initializer_list<EventType>& events, Listener* listener)
{
    assert(listener);

    m_Listeners.emplace_back(events, listener);
}

void Notifier::detachListener(Listener* listener)
{
    assert(listener);

    for (auto it = m_Listeners.begin(); it != m_Listeners.end(); ++it)
    {
        if (it->listener == listener)
        {
            m_Listeners.erase(it);
            return;
        }
    }
}

void Notifier::notify(Event* event)
{
    for (auto listenerInfo : m_Listeners)
    {
        for (auto eventType : listenerInfo.types)
        {
            if (eventType == event->getType())
            {
                listenerInfo.listener->onEvent(event);
            }
        }
    }
}

}