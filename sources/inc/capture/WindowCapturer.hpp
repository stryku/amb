#pragma once

#include "graphics/Image.hpp"

#include <Windows.h>

#include <type_traits>

#include <boost/optional.hpp>

#include <QDebug>

namespace Amb
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

            void captureWindow(HWND windowHandle, const Rect& clientRect, Graphics::Image &img, boost::optional<Rect> rect = {})
            {
                //Rect rc = rect ? rect.get() : clientRect;
                Rect rc = clientRect;

                Graphics::Image fullWindow;

                fullWindow.w = rc.w;
                fullWindow.h = rc.h;
                fullWindow.resize();

                HBITMAP hbmp = CreateCompatibleBitmap(hScreen,
                                                      rc.w, rc.h);
                SelectObject(hDC, hbmp);

                static_cast<CaptureDetails*>(this)->captureWindowImpl(windowHandle, 
                                                                      Rect{ static_cast<int>(rc.x), 
                                                                            static_cast<int>(rc.y),
                                                                            static_cast<size_t>(rc.w),
                                                                            static_cast<size_t>(rc.h)});

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
                    fullWindow.pixelsPtr(), &MyBMInfo, DIB_RGB_COLORS))
                {
                    // error handling
                }

                DeleteObject(hbmp);

                img = fullWindow.getSprite(rect.get());

                //return img;
            }

        protected:
            HDC hScreen{ NULL };
            HDC hDC{ NULL };

        private:
            RECT getRectToCapture(const Rect& clientRect, const boost::optional<Rect> &rect) const
            {
                RECT rc;
                const auto r = rect.get();

                if (rect)
                {
                    rc.left = r.x;
                    rc.top = r.y;
                    rc.bottom = rc.top + r.h;
                    rc.right = rc.left + r.w;
                }
                else
                {
                    rc.left = clientRect.x;
                    rc.top = clientRect.y;
                    rc.right = rc.left + clientRect.w;
                    rc.bottom = rc.top + clientRect.h;
                }

                return rc;
            }
        };
    }
}
