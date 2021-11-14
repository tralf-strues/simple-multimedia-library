/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file system_event_manager.cpp
 * @date 2021-10-04
 * 
 * @copyright Copyright (c) 2021
 */

#include <SDL.h>
#include "events/system_event_manager.h"

namespace Sml
{
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
                return new MouseMovedEvent{nativeEvent->motion.x, nativeEvent->motion.y,
                                           nativeEvent->motion.xrel, nativeEvent->motion.yrel};
            }

            case SDL_MOUSEBUTTONDOWN:
            {
                return new MouseButtonPressedEvent{nativeEvent->motion.x, nativeEvent->motion.y,
                                                   convertNativeButton(nativeEvent->button.button)};
            }

            case SDL_MOUSEBUTTONUP:
            {
                return new MouseButtonReleasedEvent{nativeEvent->motion.x, nativeEvent->motion.y,
                                                    convertNativeButton(nativeEvent->button.button)};
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
}