#pragma once

#include "utils.hpp"
#include "TibiaFinder.hpp"

#include <Windows.h>

#include <thread>

namespace Amb
{
    struct Pos;

    namespace Simulate
    {
        class Simulator
        {
        public:
            Simulator()
            {}
            ~Simulator()
            {}

            void mouseClick(const Pos &pos) const;

            void hotkey( Utils::Hotkey hotkey,
                         Utils::RandomBetween RandomBetween = { defMinRandomBetween, defMaxRandomBetween } );

            void keyDownAndUp( WPARAM key,
                               Utils::RandomBetween RandomBetween = { defMinRandomBetween, defMaxRandomBetween } );

            void ctrlDown();
            void ctrlUp();
            void shiftDown();
            void shiftUp();

            void attachToNewWindow(HWND hwnd);

        private:
            static const size_t defMinRandomBetween = 15;
            static const size_t defMaxRandomBetween = 50;

            HWND windowHwnd;

            static WPARAM hotkeyToWparam(Utils::Hotkey hotkey);
        };
    }
}
