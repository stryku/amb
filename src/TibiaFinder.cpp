#include "TibiaFinder.hpp"

namespace AMB
{
    namespace Utils
    {
        std::wstring TibiaFinder::getWindowTitle( HWND hwnd )
        {
            const size_t maxTitleLength = 256;

            wchar_t title[maxTitleLength];

            GetWindowTextW( hwnd,
                           reinterpret_cast<LPWSTR>( title ),
                           maxTitleLength );

            return title;
        }

        BOOL CALLBACK TibiaFinder::checkWindowTitle( HWND hwnd, LPARAM lParam )
        {
            auto &resultVector = *reinterpret_cast<std::vector<std::wstring>*>( lParam );
            auto windowTitle = getWindowTitle( hwnd );
            std::wstring pattern( L"Tibia - " );

            if( windowTitle.find( pattern ) != std::wstring::npos )
                resultVector.push_back( windowTitle );

            return TRUE;
        }

        std::vector<std::wstring> TibiaFinder::findAllClientsTitles()
        {
            std::vector<std::wstring> results;

            EnumWindows( checkWindowTitle,
                         reinterpret_cast<LPARAM>( &results ) );

            return results;
        }
    }
}
