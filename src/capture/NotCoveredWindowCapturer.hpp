#pragma once

#include "capture/WindowCapturer.hpp"
#include "graphics/Image.hpp"

namespace AMB
{
    namespace Capture
    {
        class NotCoveredWindowCapturer : AMB::Capture::WindowCapturer<NotCoveredWindowCapturer>
        {
        public:
            void captureWindowImpl(HWND windowHandle, const Rect &rc)
            {
                BitBlt(hDC, 0, 0, rc.w, rc.h, hScreen, rc.x, rc.y, SRCCOPY);
            }
        };
    }
}
