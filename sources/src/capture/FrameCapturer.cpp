#include "capture/FrameCapturer.hpp"
#include "graphics/Image.hpp"

namespace Amb
{
    namespace Capture
    {
        FrameCapturer::FrameCapturer(Graphics::Image &screen, const Rect &clientRect)
            : screen{ screen }
            , clientRect{ clientRect }
        {}

        void FrameCapturer::setCaptureMode(const Mode::CaptureMode newCaptureMode)
        {
            captureMode = newCaptureMode;
        }

        void FrameCapturer::attachToNewWindow(HWND newWindowHandle)
        {
            windowHandle = newWindowHandle;
        }

        void FrameCapturer::newFrame(const boost::optional<Rect> &rect)
        {
            if (captureMode == Mode::CaptureMode::OnlyCovered)
                screenCapturerCovered.captureWindow(windowHandle, clientRect, screen, rect);
            else
                screenCapturerNotCovered.captureWindow(windowHandle, clientRect, screen, rect);

            screen.toCb();
        }
    }
}
