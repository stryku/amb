#pragma once

#include "capture/WindowCapturer.hpp"
#include "graphics/Image.hpp"

namespace AMB
{
    namespace Capture
    {
        class CoveredWindowCapturer : AMB::Capture::WindowCapturer<CoveredWindowCapturer>
        {
        public:
            void captureWindowImpl(HWND windowHandle, Rect)
            {
                PrintWindow(windowHandle, hDC, PW_CLIENTONLY);
            }
        };
    }
}
