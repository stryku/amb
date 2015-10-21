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

        std::string hotkeyToStdString( Hotkey hot )
        {
            switch( hotkey )
            {
                case Utils::Hotkey::F1: return "F1";
                case Utils::Hotkey::F2: return "F2";
                case Utils::Hotkey::F3: return "F3";
                case Utils::Hotkey::F4: return "F4";
                case Utils::Hotkey::F5: return "F5";
                case Utils::Hotkey::F6: return "F6";
                case Utils::Hotkey::F7: return "F7";
                case Utils::Hotkey::F8: return "F8";
                case Utils::Hotkey::F9: return "F9";
                case Utils::Hotkey::F10: return "F10";
                case Utils::Hotkey::F11: return "F11";
                case Utils::Hotkey::F12: return "F12";

                default: return "UNKNOW";
            }
        }

        Hotkey stdStringToHotkey( const std::string &str )
        {
            if( str == "F1" ) return Hotkey::F1;
            if( str == "F2" ) return Hotkey::F2;
            if( str == "F3" ) return Hotkey::F3;
            if( str == "F4" ) return Hotkey::F4;
            if( str == "F5" ) return Hotkey::F5;
            if( str == "F6" ) return Hotkey::F6;
            if( str == "F7" ) return Hotkey::F7;
            if( str == "F8" ) return Hotkey::F8;
            if( str == "F9" ) return Hotkey::F9;
            if( str == "F10" ) return Hotkey::F10;
            if( str == "F11" ) return Hotkey::F11;
            if( str == "F12" ) return Hotkey::F12;

            return Hotkey::UNKNOWN;
        }

        struct RandomBetween
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
