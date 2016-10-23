#pragma once

#include "utils.hpp"
#include "TibiaFinder.hpp"

#include <Windows.h>

#include <thread>

namespace AMB
{
    namespace Simulate
    {
        class Simulator
        {
        private:
            static const size_t defMinRandomBetween = 15;
            static const size_t defMaxRandomBetween = 50;

            HWND windowHwnd;

            static WPARAM hotkeyToWparam( Utils::Hotkey hotkey );

        public:
            Simulator()
            {}
            ~Simulator()
            {}

            void hotkey( Utils::Hotkey hotkey,
                         Utils::RandomBetween RandomBetween = { defMinRandomBetween, defMaxRandomBetween } );

            void keyDownAndUp( WPARAM key,
                               Utils::RandomBetween RandomBetween = { defMinRandomBetween, defMaxRandomBetween } );

            void attachToNewWindow(HWND hwnd);
        };
    }
}
