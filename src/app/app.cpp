/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file app.cpp
 * @date 2021-11-07
 * 
 * @copyright Copyright (c) 2021
 */

#include <assert.h>
#include <SDL.h>
#include "app/app.h"

namespace Sml
{
    Application::Application(int32_t argc, const char* argv[]) : m_CommandLineArguments(argc)
    {
        for (int32_t i = 0; i < argc; ++i)
        {
            m_CommandLineArguments[i] = argv[i];
        }
    }

    int Application::run()
    {
        onInit();

        m_Running = true;

        while (m_Running)
        {
            uint32_t frameStartTime = SDL_GetTicks();

            onUpdate();

            uint32_t frameEndTime = SDL_GetTicks();

            if (frameStartTime != frameEndTime)
            {
                m_UpdateFps = 1e3 / (frameEndTime - frameStartTime);
            }
            else
            {
                m_UpdateFps = std::numeric_limits<uint32_t>::max();
            }
        }

        return onQuit();
    }

    void Application::stop()
    {
        m_Running = false;
    }

    const char* Application::getCommandLineArgument(uint32_t i)
    {
        assert(i < m_CommandLineArguments.size());

        return m_CommandLineArguments[i];
    }

    uint32_t Application::getFps()
    {
        return m_UpdateFps;
    }
}