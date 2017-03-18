#pragma once

#include <string>

namespace Amb
{
    namespace Client
    {
        enum class Hotkey
        {
            F1 = 0,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
            F8,
            F9,
            F10,
            F11,
            F12,

            UNKNOWN
        };

        std::string hotkeyToStdString(Hotkey hotkey);
        Hotkey stdStringToHotkey(const std::string &str);
        Hotkey size_tToHotkey(size_t hotkey);
        std::string size_tHotkeyToStdString(size_t hotkey);
        size_t hotkeyToSize_t(Hotkey hot);
    }
}