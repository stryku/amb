#include "utils.hpp"
#include <iostream>
#include <locale>
#include <codecvt>

namespace Amb
{
    namespace Utils
    {
        std::string hotkeyToStdString( Hotkey hotkey )
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

        size_t hotkeyToSize_t(Hotkey hot)
        {
            switch (hot)
            {
            case Amb::Utils::Hotkey::F1: return 0;
            case Amb::Utils::Hotkey::F2: return 1;
            case Amb::Utils::Hotkey::F3: return 2;
            case Amb::Utils::Hotkey::F4: return 3;
            case Amb::Utils::Hotkey::F5: return 4;
            case Amb::Utils::Hotkey::F6: return 5;
            case Amb::Utils::Hotkey::F7: return 6;
            case Amb::Utils::Hotkey::F8: return 7;
            case Amb::Utils::Hotkey::F9: return 8;
            case Amb::Utils::Hotkey::F10: return 9;
            case Amb::Utils::Hotkey::F11: return 10;
            case Amb::Utils::Hotkey::F12: return 11;

            case Amb::Utils::Hotkey::UNKNOWN:
            default:
                return -1;
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

        Hotkey size_tToHotkey( size_t hotkey )
        {
            switch( hotkey )
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

        std::string size_tHotkeyToStdString( size_t hotkey )
        {
            switch( hotkey )
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

        size_t RandomBetween::get() const
        {
            static std::random_device rd;
            static std::mt19937 mt( rd() );
            std::uniform_int_distribution<size_t> dist( min, max );

            return dist( mt );
        }

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

        DWORD getModuleBase( DWORD pid, const char *sModuleName = "Tibia.exe" )
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
                for( DWORD i = 0; i < cModules / sizeof( HMODULE ); ++i )
                {
                    if( GetModuleBaseNameA( hProc, hModules[i],  szBuf, sizeof( szBuf ) ) )
                    {
                        if( _strcmpi( szBuf, sModuleName ) == 0 )
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

        std::string readWholeFileIntoString(const std::string &path)
        {
            std::ifstream t(path);
            t.seekg(0, std::ios::end);
            size_t size = t.tellg();
            std::string buffer(size, ' ');
            t.seekg(0);
            t.read(&buffer[0], size);
            return buffer;
        }

        std::wstring stringToWstring(const std::string& str)
        {
            using convert_typeX = std::codecvt_utf8<wchar_t>;
            std::wstring_convert<convert_typeX, wchar_t> converterX;

            return converterX.from_bytes(str);
        }

        std::string wstringToString(const std::wstring& wstr)
        {
            using convert_typeX = std::codecvt_utf8<wchar_t>;
            std::wstring_convert<convert_typeX, wchar_t> converterX;

            return converterX.to_bytes(wstr);
        }
    }
}
