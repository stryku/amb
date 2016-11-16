#pragma once

#include "graphics/Image.hpp"

#include <Windows.h>

#include <type_traits>

namespace AMB
{
    namespace Capture
    {
        template <typename CaptureDetails = void>
        class WindowCapturer
        {
        public:
            WindowCapturer()
                : hScreen{ GetDC(NULL) }
                , hDC{ CreateCompatibleDC(hScreen) }
            {}

            ~WindowCapturer()
            {
                DeleteDC(hDC);
                ReleaseDC(NULL, hScreen);
            }

            void captureWindow(HWND windowHandle, Graphics::Image &img)
            {
                //Graphics::Image img;
                RECT rc;
                GetClientRect(windowHandle, &rc);
                if (rc.bottom == 0 && rc.right == 0)
                {
                    qDebug("Window is minimized!");
                    //return{};
                }

                img.w = rc.right - rc.left;
                img.h = rc.bottom - rc.top;
                img.resize();

                HBITMAP hbmp = CreateCompatibleBitmap(hScreen,
                                                      rc.right - rc.left, rc.bottom - rc.top);
                SelectObject(hDC, hbmp);

                static_cast<CaptureDetails*>(this)->captureWindowImpl(windowHandle, 
                                                                      Rect{ static_cast<int>(rc.left), 
                                                                            static_cast<int>(rc.top),
                                                                            static_cast<size_t>(img.w),
                                                                            static_cast<size_t>(img.h)});

                BITMAPINFO MyBMInfo = { 0 };
                MyBMInfo.bmiHeader.biSize = sizeof(MyBMInfo.bmiHeader);

                if (0 == GetDIBits(hDC, hbmp, 0, 0, NULL, &MyBMInfo, DIB_RGB_COLORS))
                {
                    // error handling
                }

                MyBMInfo.bmiHeader.biBitCount = 32;
                MyBMInfo.bmiHeader.biCompression = BI_RGB;  // no compression -> easier to use
                                                            // correct the bottom-up ordering of lines (abs is in cstdblib and stdlib.h)
                MyBMInfo.bmiHeader.biHeight = abs(MyBMInfo.bmiHeader.biHeight);

                if (0 == GetDIBits(hDC, hbmp, 0, MyBMInfo.bmiHeader.biHeight,
                    img.pixelsPtr(), &MyBMInfo, DIB_RGB_COLORS))
                {
                    // error handling
                }

                DeleteObject(hbmp);

                //return img;
            }

        protected:
            HDC hScreen{ NULL };
            HDC hDC{ NULL };
        };
    }
}
