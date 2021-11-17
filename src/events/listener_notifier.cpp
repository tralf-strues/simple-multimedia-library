/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file listener_notifier.cpp
 * @date 2021-10-04
 * 
 * @copyright Copyright (c) 2021
 */

#include <algorithm>
#include "events/listener_notifier.h"

namespace Sml
{
    Notifier::~Notifier()
    {
        for (auto pair : m_Listeners)
        {
            for (auto listener : *pair.second)
            {
                delete listener;
            }

            delete pair.second;
        }
    }

    void Notifier::attachListener(const std::initializer_list<EventType>& events, Listener* listener)
    {
        assert(listener);

        for (auto eventType : events)
        {
            auto foundListIt = m_Listeners.find(eventType);

            if (foundListIt == m_Listeners.end())
            {
                std::list<Listener*>* newList = new std::list<Listener*>();
                newList->push_back(listener);

                m_Listeners[eventType] = newList;
            }
            else
            {
                (*foundListIt).second->push_back(listener);
            }
        }
    }

    void Notifier::detachListener(Listener* listener)
    {
        assert(listener);

        for (auto pair : m_Listeners)
        {
            std::list<Listener*>* listenersList = pair.second;
            auto listenerIt = std::find(listenersList->begin(), listenersList->end(), listener);

            if (listenerIt != listenersList->end())
            {
                listenersList->erase(listenerIt);
            }
        }
    }

    void Notifier::notify(Event* event)
    {
        assert(event);

        for (auto pair : m_Listeners)
        {
            if (pair.first == event->getType())
            {
                for (Listener* listener : *pair.second)
                {
                    listener->onEvent(event);
                }
            }
        }
    }
}