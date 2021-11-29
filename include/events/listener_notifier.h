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
    #define DEFINE_STATIC_LISTENED_EVENT_TYPES(...) \
        static constexpr std::initializer_list<Sml::EventType> EVENT_TYPES{__VA_ARGS__};

    #define DEFINE_STATIC_LISTENED_EVENT_TYPES_FROM_BASE_CLASS(baseClass) \
        static constexpr std::initializer_list<Sml::EventType> EVENT_TYPES = baseClass::EVENT_TYPES;

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
