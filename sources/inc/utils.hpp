#pragma once

#include <Windows.h>
#include <Psapi.h>

#include <random>
#include <mutex>
#include <fstream>

#include <QLineEdit>

namespace Amb
{
    namespace Utils
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


        struct RandomBetween
        {
            size_t min, max;

            size_t get() const;
        };

        struct Pos
        {
            int x, y;
        };

        struct Rect
        {
            int x, y;
            size_t w, h;
        };

        void closeAndNullHandle(HANDLE &handle);

        void safeCloseAndNullHandle(HANDLE &handle);

        DWORD getModuleBase(DWORD pid, const char *sModuleName);

        template <typename T>
        auto getFromToFromEdits(const T &fromToEdits)
        {
            return FromTo{
                fromToEdits.from->text().toInt(),
                fromToEdits.to->text().toInt()
            };
        }

        std::string readWholeFileIntoString(const std::string &path);
        std::string wstringToString(const std::wstring &wstr);
        std::wstring stringToWstring(const std::string &str);
    }


}
