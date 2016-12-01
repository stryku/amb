#pragma once

#include "capture/WindowCapturer.hpp"
#include "graphics/Image.hpp"

namespace Amb
{
    namespace Capture
    {
        class CoveredWindowCapturer : public Amb::Capture::WindowCapturer<CoveredWindowCapturer>
        {
        public:
            void captureWindowImpl(HWND windowHandle, Rect)
            {
                PrintWindow(windowHandle, hDC, PW_CLIENTONLY);
            }
        };
    }
}
