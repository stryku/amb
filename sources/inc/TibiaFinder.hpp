#pragma once

#include <Windows.h>

#include <mutex>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>

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
            struct PidToHwndData
            {
                DWORD pid;
                HWND hwnd;
            };

            static std::wstring getWindowTitle( HWND hwnd );

            static BOOL CALLBACK checkWindowTitle( HWND hwnd, LPARAM lParam );

            static BOOL CALLBACK callbackPidToHwnd( HWND hwnd, LPARAM lParam )
            {
                DWORD lpdwProcessId;

                GetWindowThreadProcessId( hwnd,&lpdwProcessId );

                auto &data = *( reinterpret_cast<PidToHwndData*>( lParam ) );

                if( lpdwProcessId == data.pid )
                {
                    data.hwnd = hwnd;
                    return FALSE;
                }

                return TRUE;
            }

            static std::vector<std::wstring> findAllClientsTitles();

            static HWND pidToHwnd( DWORD pid )
            {
                PidToHwndData pidToHwndData;

                pidToHwndData.pid = pid;

                EnumWindows( callbackPidToHwnd, reinterpret_cast<LPARAM>( &pidToHwndData ) );

                return pidToHwndData.hwnd;
            }

            static DWORD findProcessId( const std::wstring &tibiaWindowTitle )
            {
                auto str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(tibiaWindowTitle);
                HWND hwnd = FindWindow(0, str.c_str());
                DWORD pid;

                if( hwnd == NULL )
                    return NULL;

                 GetWindowThreadProcessId( hwnd, &pid );

                 return pid;
            }
        };
    }
}
