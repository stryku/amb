#pragma once

#include <Windows.h>

#include <mutex>
#include <vector>
#include <string>

namespace AMB
{
    namespace Utils
    {
        struct TibiaClientInfo
        {
            std::string windowName;
            DWORD pid;
            HWND hwnd;
        };

        struct TibiaFinder
        {
            static std::wstring getWindowTitle( HWND hwnd );

            static BOOL CALLBACK checkWindowTitle( HWND hwnd, LPARAM lParam );

            static std::vector<std::wstring> findAllClientsTitles();
        };
    }
}
