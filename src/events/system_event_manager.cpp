//------------------------------------------------------------------------------
//! @author Nikita Mochalov (github.com/tralf-strues)
//! @file system_event_manager.cpp
//! @date 2021-10-04
//! 
//! @copyright Copyright (c) 2021
//------------------------------------------------------------------------------

#include <SDL.h>
#include "events/system_event_manager.h"

Event* convertNativeEvent(SDL_Event* nativeEvent)
{
    assert(nativeEvent);

    switch (nativeEvent->type)
    {
        case SDL_QUIT: 
        { 
            return new WindowCloseEvent{};
        }

        case SDL_KEYDOWN:
        {
            return new KeyPressedEvent{static_cast<Scancode>(nativeEvent->key.keysym.scancode)};
        }

        case SDL_MOUSEMOTION:
        {
            int32_t mouseX = 0;
            int32_t mouseY = 0;

            SDL_GetMouseState(&mouseX, &mouseY);

            return new MouseMovedEvent{mouseX, mouseY};
        }

        case SDL_MOUSEBUTTONDOWN:
        {
            int32_t mouseX = 0;
            int32_t mouseY = 0;

            SDL_GetMouseState(&mouseX, &mouseY);

            return new MouseButtonPressedEvent{mouseX, mouseY};
        }

        default: { break; }
    }

    return nullptr;
}

void SystemEventManager::proccessEvents()
{
    Event* nextEvent = nullptr;

    while ((nextEvent = pollEvent(true)) != nullptr)
    {
        delete nextEvent;
    }
}

Event* SystemEventManager::pollEvent(bool notifyListeners)
{
    static SDL_Event nativeEvent = {};
    Event* event = nullptr;

    if (SDL_PollEvent(&nativeEvent))
    {
        event = convertNativeEvent(&nativeEvent);

        if (event == nullptr)
        {
            event = new Event();
        }
        else if (notifyListeners)
        {
            notify(event);
        }
    }

    return event;
}