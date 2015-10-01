#pragma once

#include <Windows.h>

#include <random>

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

        struct SleepTime
        {
            size_t min, max;

            size_t get() const
            {
                static std::random_device rd;
                static std::mt19937 mt( rd() );
                std::uniform_real_distribution<size_t> dist( min, max );

                return dist( mt );
            }
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