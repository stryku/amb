#include "Simulator.hpp"
#include <QtDebug>

namespace Amb
{
    namespace Simulate
    {
        WPARAM Simulator::hotkeyToWparam( Utils::Hotkey hotkey )
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

        void Simulator::hotkey( Utils::Hotkey hotkey,
                                Utils::RandomBetween randomBetween )
        {
            qDebug("simulating hotkey: %d", static_cast<int>(hotkey));
            keyDownAndUp( hotkeyToWparam( hotkey ),
                          randomBetween );
        }

        void Simulator::keyDownAndUp( WPARAM key,
                                      Utils::RandomBetween randomBetween )
        {
            std::this_thread::sleep_for( std::chrono::milliseconds( randomBetween.get() ) );
            PostMessage( windowHwnd, WM_KEYDOWN, key, 0 );
            std::this_thread::sleep_for( std::chrono::milliseconds( randomBetween.get() ) );
            PostMessage( windowHwnd, WM_KEYUP, key, 0 );
            std::this_thread::sleep_for( std::chrono::milliseconds( randomBetween.get() ) );
        }

        void Simulator::attachToNewWindow(HWND hwnd)
        {
            windowHwnd = hwnd;
        }

        void Simulator::mouseClick(const Pos &pos) const
        {
            PostMessage(windowHwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(500, 200));
            PostMessage(windowHwnd, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(500, 200));
        }

        void Simulator::ctrlDown()
        {
            PostMessage(windowHwnd, WM_KEYDOWN, VK_CONTROL, 0);
        }
        void Simulator::ctrlUp()
        {
            PostMessage(windowHwnd, WM_KEYUP, VK_CONTROL, 0);
        }

        void Simulator::shiftDown()
        {
            PostMessage(windowHwnd, WM_KEYDOWN, VK_SHIFT, 0);
        }
        void Simulator::shiftUp()
        {
            PostMessage(windowHwnd, WM_KEYUP, VK_SHIFT, 0);
        }

    }
}
