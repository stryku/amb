#pragma once

#include <Windows.h>

#include <mutex>

namespace AMB
{
    namespace Utils
    {
        struct TibiaFinder
        {
            static std::mutex mtx;
            static HWND findedHwnd;


            static BOOL CALLBACK EnumWindowsProcMy( HWND hwnd, LPARAM lParam )
            {
                DWORD lpdwProcessId;
                GetWindowThreadProcessId( hwnd, &lpdwProcessId );
                if( lpdwProcessId == lParam )
                {
                    findedHwnd = hwnd;
                    return FALSE;
                }
                return TRUE;
            }

            static void findHwnd( DWORD pid, HWND &outHwnd )
            {
                std::lock_guard<std::mutex> lock( mtx );

                EnumWindows( EnumWindowsProcMy, pid );

                outHwnd = findedHwnd;
            }
        };
        std::mutex TibiaWindowHwndFinder::mtx;
        HWND TibiaWindowHwndFinder::findedHwnd;
    }
}
