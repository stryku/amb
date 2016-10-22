#pragma once

#include <Windows.h>
#include <Psapi.h>

#include <random>
#include <mutex>

namespace AMB
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

        std::string hotkeyToStdString( Hotkey hotkey );

        Hotkey stdStringToHotkey( const std::string &str );

        Hotkey size_tToHotkey( size_t hotkey );

        std::string size_tHotkeyToStdString( size_t hotkey );

        struct RandomBetween
        {
            size_t min, max;

            size_t get() const;
        };

        void closeAndNullHandle( HANDLE &handle );

        void safeCloseAndNullHandle( HANDLE &handle );

        DWORD getModuleBase( DWORD pid, const char *sModuleName );
    }
}
