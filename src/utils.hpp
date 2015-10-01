#pragma once

#include <Windows.h>

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
            F12
        };

        void closeAndNullHandle( HANDLE &handle )
        {
            CloseHandle( handle );
            handle = NULL;
        }

        void safeCloseAndNullHandle( HANDLE &handle )
        {
            if( handle != NULL )
                closeAndNullHandle( handle );
        }
    }
}