/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file app.h
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include "../containers/array.h"

namespace Sml
{
    class Application
    {
    public:
        Application(int32_t argc, char* argv[]) : m_Arguments(argc)
        {
            for (int32_t i = 0; i < argc; ++i)
            {
                m_Arguments[i] = argv[i];
            }
        }

        virtual void run() = 0;

    private:
        Array<char*> m_Arguments;
    };
}
