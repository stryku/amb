#include "utils.hpp"
#include "graphics/Image.hpp"

#include <iostream>
#include <locale>
#include <codecvt>

namespace Amb
{
    namespace Utils
    {
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

            if (!t.is_open())
                return{};

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

        std::string imageToSimpleString(const Graphics::Image& img)
        {
            std::string out;
            for (const auto &pixel : img.pixels)
            {
                out += std::to_string(pixel.r) + " "
                    + std::to_string(pixel.g) + " "
                    + std::to_string(pixel.b) + " "
                    + std::to_string(pixel.a) + " ";
            }

            return out;
        }
    }
}
