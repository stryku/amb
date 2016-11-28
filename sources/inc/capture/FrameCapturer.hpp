#pragma once

#include "capture/CaptureMode.hpp"
#include "capture/NotCoveredWindowCapturer.hpp"
#include "capture/CoveredWindowCapturer.hpp"

namespace Amb
{
    namespace Graphics
    {
        struct Image;
    }

    namespace Capture
    {
        class FrameCapturer
        {
        public:
            FrameCapturer(Graphics::Image &screen, const Rect &clientRect);

            void setCaptureMode(Mode::CaptureMode newCaptureMode);
            void attachToNewWindow(HWND windowHandle);
            void newFrame(const boost::optional<Rect> &rect = {});

        private:
            Graphics::Image &screen;
            const Rect &clientRect;
            Mode::CaptureMode captureMode;
            HWND windowHandle;

            NotCoveredWindowCapturer screenCapturerNotCovered;
            CoveredWindowCapturer screenCapturerCovered;
        };
    }
}
