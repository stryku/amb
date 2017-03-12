#include "client/Hotkey.hpp"

namespace Amb
{
    namespace Client
    {
        std::string hotkeyToStdString(Hotkey hotkey)
        {
            switch (hotkey)
            {
            case Hotkey::F1: return "F1";
            case Hotkey::F2: return "F2";
            case Hotkey::F3: return "F3";
            case Hotkey::F4: return "F4";
            case Hotkey::F5: return "F5";
            case Hotkey::F6: return "F6";
            case Hotkey::F7: return "F7";
            case Hotkey::F8: return "F8";
            case Hotkey::F9: return "F9";
            case Hotkey::F10: return "F10";
            case Hotkey::F11: return "F11";
            case Hotkey::F12: return "F12";

            default: return "UNKNOW";
            }
        }

        size_t hotkeyToSize_t(Hotkey hot)
        {
            switch (hot)
            {
            case Hotkey::F1: return 0;
            case Hotkey::F2: return 1;
            case Hotkey::F3: return 2;
            case Hotkey::F4: return 3;
            case Hotkey::F5: return 4;
            case Hotkey::F6: return 5;
            case Hotkey::F7: return 6;
            case Hotkey::F8: return 7;
            case Hotkey::F9: return 8;
            case Hotkey::F10: return 9;
            case Hotkey::F11: return 10;
            case Hotkey::F12: return 11;

            case Hotkey::UNKNOWN:
            default:
                return -1;
            }
        }

        Hotkey stdStringToHotkey(const std::string &str)
        {
            if (str == "F1") return Hotkey::F1;
            if (str == "F2") return Hotkey::F2;
            if (str == "F3") return Hotkey::F3;
            if (str == "F4") return Hotkey::F4;
            if (str == "F5") return Hotkey::F5;
            if (str == "F6") return Hotkey::F6;
            if (str == "F7") return Hotkey::F7;
            if (str == "F8") return Hotkey::F8;
            if (str == "F9") return Hotkey::F9;
            if (str == "F10") return Hotkey::F10;
            if (str == "F11") return Hotkey::F11;
            if (str == "F12") return Hotkey::F12;

            return Hotkey::UNKNOWN;
        }

        Hotkey size_tToHotkey(size_t hotkey)
        {
            switch (hotkey)
            {
            case 0: return Hotkey::F1;
            case 1: return Hotkey::F2;
            case 2: return Hotkey::F3;
            case 3: return Hotkey::F4;
            case 4: return Hotkey::F5;
            case 5: return Hotkey::F6;
            case 6: return Hotkey::F7;
            case 7: return Hotkey::F8;
            case 8: return Hotkey::F9;
            case 9: return Hotkey::F10;
            case 10: return Hotkey::F11;
            case 11: return Hotkey::F12;

            default: return Hotkey::UNKNOWN;
            }
        }

        std::string size_tHotkeyToStdString(size_t hotkey)
        {
            switch (hotkey)
            {
            case 0: return "F1";
            case 1: return "F2";
            case 2: return "F3";
            case 3: return "F4";
            case 4: return "F5";
            case 5: return "F6";
            case 6: return "F7";
            case 7: return "F8";
            case 8: return "F9";
            case 9: return "F10";
            case 10: return "F11";
            case 11: return "F12";

            default: return "UNKNOW";
            }
        }

    }
}
