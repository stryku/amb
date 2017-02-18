#pragma once

#include "graphics/Image.hpp"

#include <array>

namespace Amb
{
    namespace Readers
    {
        namespace details
        {
            class ScreenCapturer
            {
            public:
                ScreenCapturer(Graphics::Image &screen)
                    : hScreen{ GetDC(NULL) }
                    , hDC{ CreateCompatibleDC(hScreen) }
                    , screen{ screen }
                {}

                ~ScreenCapturer()
                {
                    DeleteDC(hDC);
                    ReleaseDC(NULL, hScreen);
                }

                Graphics::Image captureWindow(HWND windowHandle)
                {
                    Graphics::Image img;
                    RECT rc;
                    GetClientRect(windowHandle, &rc);
                    if (rc.bottom == 0 && rc.right == 0)
                    {
                        LOG_DEBUG("Window is minimized!");
                        return {};
                    }

                    img.w = rc.right - rc.left;
                    img.h = rc.bottom - rc.top;
                    img.resize();

                    HBITMAP hbmp = CreateCompatibleBitmap(hScreen,
                                                          rc.right - rc.left, rc.bottom - rc.top);
                    SelectObject(hDC, hbmp);

                    PrintWindow(windowHandle, hDC, PW_CLIENTONLY);


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

                    return img;
                }

                std::vector<Rgba> capture(size_t x, size_t y, size_t w, size_t h)
                {
                    BITMAPINFO MyBMInfo = { 0 };
                    MyBMInfo.bmiHeader.biSize = sizeof(MyBMInfo.bmiHeader);

                    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
                    HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
                    BOOL    bRet = BitBlt(hDC, 0, 0, w, h, hScreen, x, y, SRCCOPY);

                    if (0 == GetDIBits(hDC, hBitmap, 0, 0, NULL, &MyBMInfo, DIB_RGB_COLORS))
                    {
                        // error handling
                    }
                    std::vector<Rgba> ret(w*h);

                    MyBMInfo.bmiHeader.biBitCount = 32;
                    MyBMInfo.bmiHeader.biCompression = BI_RGB;  // no compression -> easier to use
                                                                // correct the bottom-up ordering of lines (abs is in cstdblib and stdlib.h)
                    MyBMInfo.bmiHeader.biHeight = abs(MyBMInfo.bmiHeader.biHeight);

                    // Call GetDIBits a second time, this time to (format and) store the actual
                    // bitmap data (the "pixels") in the buffer lpPixels
                    if (0 == GetDIBits(hDC, hBitmap, 0, MyBMInfo.bmiHeader.biHeight,
                        &ret[0], &MyBMInfo, DIB_RGB_COLORS))
                    {
                        // error handling
                    }

                    DeleteObject(hBitmap);
                    return ret;
                }

                Rgba& getPixel(int x, int y)
                {
                    return screen.pixel(x, y);
                }

                void toCb()
                {
                    screen.toCb();
                }

                void recapture(HWND windowHandle)
                {
                    screen = captureWindow(windowHandle);
                }

            private:
                HDC     hScreen = GetDC(NULL);
                HDC     hDC = CreateCompatibleDC(hScreen);
                Graphics::Image &screen;
            };
        }
    }
}
