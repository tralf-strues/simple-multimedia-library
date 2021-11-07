/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file app.h
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include <stdint.h>
#include <vector>

namespace Sml
{
    class Application
    {
    public:
        Application(int32_t argc, const char* argv[]);
        
        virtual void onInit() {};
        virtual void onUpdate() {};
        virtual int onQuit() { return 0; };

        int run();
        void stop();

        const char* getCommandLineArgument(uint32_t i);
        uint32_t    getFps();

    private:
        std::vector<const char*> m_CommandLineArguments;
        bool                     m_Running   = false;
        uint32_t                 m_UpdateFps = 0;
    };
}
