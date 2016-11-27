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
            FrameCapturer(Graphics::Image &screen, boost::optional<Rect> frameRect = {});

            void set(Mode::CaptureMode newCaptureMode);
            void attachToNewWindow(HWND windowHandle);
            void newFrame();
            void newFrame(const boost::optional<Rect> &rect);

        private:
            Graphics::Image &screen;
            boost::optional<Rect> frameRect;
            Mode::CaptureMode captureMode;
            HWND windowHandle;

            NotCoveredWndCapturer screenCapturerNotCovered;
            CoveredWndCapturer screenCapturerCovered;
        };
    }
}
