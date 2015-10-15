#pragma once

#include "utils.hpp"
#include "TibiaWindowHwndFinder.hpp"

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

            WPARAM hotkeyToWparam( Utils::Hotkey hotkey )
            {
                switch( hotkey )
                {
                    case Utils::Hotkey::F1: return VK_F1;
                    case Utils::Hotkey::F2: return VK_F2;
                    case Utils::Hotkey::F3: return VK_F3;
                    case Utils::Hotkey::F4: return VK_F4;
                    case Utils::Hotkey::F5: return VK_F5;
                    case Utils::Hotkey::F6: return VK_F6;
                    case Utils::Hotkey::F7: return VK_F7;
                    case Utils::Hotkey::F8: return VK_F8;
                    case Utils::Hotkey::F9: return VK_F9;
                    case Utils::Hotkey::F10: return VK_F10;
                    case Utils::Hotkey::F11: return VK_F11;
                    case Utils::Hotkey::F12: return VK_F12;
                }
            }

        public:
            Simulator( DWORD pid )
            {
                Utils::TibiaWindowHwndFinder::find( pid, windowHwnd );
            }
            ~Simulator()
            {}

            void hotkey( Utils::Hotkey hotkey,
                         Utils::RandomBetween RandomBetween = { defMinRandomBetween, defMaxRandomBetween } )
            {
                keyDownAndUp( hotkeyToWparam( hotkey ),
                              RandomBetween );
            }

            void keyDownAndUp( WPARAM key,
                               Utils::RandomBetween RandomBetween = { defMinRandomBetween, defMaxRandomBetween } )
            {
                std::this_thread::sleep_for( std::chrono::milliseconds( RandomBetween.get() ) );
                PostMessage( windowHwnd, WM_KEYDOWN, key, 0 );
                std::this_thread::sleep_for( std::chrono::milliseconds( RandomBetween.get() ) );
                PostMessage( windowHwnd, WM_KEYUP, key, 0 );
                std::this_thread::sleep_for( std::chrono::milliseconds( RandomBetween.get() ) );
            }
        };
    }
}