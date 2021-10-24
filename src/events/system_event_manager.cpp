//------------------------------------------------------------------------------
//! @author Nikita Mochalov (github.com/tralf-strues)
//! @file system_event_manager.cpp
//! @date 2021-10-04
//! 
//! @copyright Copyright (c) 2021
//------------------------------------------------------------------------------

#include <SDL.h>
#include "events/system_event_manager.h"

void SystemEventManager::proccessEvents()
{
    SDL_Event nativeEvent = {};
    while (SDL_PollEvent(&nativeEvent))
    {
        switch (nativeEvent.type)
        {
            case SDL_QUIT: 
            { 
                WindowCloseEvent event;
                notify(&event);
                break; 
            }

            case SDL_KEYDOWN:
            {
                KeyPressedEvent event{(Scancode) nativeEvent.key.keysym.scancode};
                notify(&event);
                break;
            }

            case SDL_MOUSEMOTION:
            {
                int32_t mouseX = 0;
                int32_t mouseY = 0;

                SDL_GetMouseState(&mouseX, &mouseY);

                MouseMovedEvent event{mouseX, mouseY};
                notify(&event);

                break;
            }

            default: { break; }
        }
    }
}