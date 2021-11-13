/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file observable_property.h
 * @date 2021-11-13
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include "listener_notifier.h"
#include "system_events.h"

namespace Sml
{
    template<typename T>
    class PropertyChangeEvent : public Event
    {
    public:
        PropertyChangeEvent(T prevValue, T newValue);

    

    private:
        T m_PrevValue;
        T m_NewValue;
    };

    template<typename T>
    class ObservableProperty : protected Notifier
    {
    public:


    private:
        T m_Property;
    };
}