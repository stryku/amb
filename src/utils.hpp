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
            F12
        };

        struct SleepTime
        {
            size_t min, max;

            size_t get() const
            {
                static std::random_device rd;
                static std::mt19937 mt( rd() );
                std::uniform_real_distribution<double> dist( min, max );

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

        DWORD getModuleBase( DWORD pid, const char *sModuleName )
        {

            auto hProc = OpenProcess( PROCESS_ALL_ACCESS,
                                      TRUE,
                                      pid );
            HMODULE *hModules = nullptr;
            char szBuf[50];
            DWORD cModules;
            DWORD dwBase = -1;
            //------ 

            EnumProcessModules( hProc, hModules, 0, &cModules );
            hModules = new HMODULE[cModules / sizeof( HMODULE )];

            if( EnumProcessModules( hProc, hModules, cModules / sizeof( HMODULE ), &cModules ) )
            {
                for( int i = 0; i < cModules / sizeof( HMODULE ); i++ )
                {
                    if( GetModuleBaseNameA( hProc, hModules[i],  szBuf, sizeof( szBuf ) ) )
                    {
                        if( _strcmpi( szBuf, "Tibia.exe" ) == 0 )
                        {
                            dwBase = (DWORD)hModules[i];
                            break;
                        }
                    }
                }
            }

            delete[] hModules;

            CloseHandle( hProc );

            return dwBase;
        }
    }
}