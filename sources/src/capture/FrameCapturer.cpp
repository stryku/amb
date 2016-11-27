#include "capture/FrameCapturer.hpp"
#include "graphics/Image.hpp"

namespace Amb
{
    namespace Capture
    {
        FrameCapturer::FrameCapturer(Graphics::Image &screen, boost::optional<Rect> frameRect)
            : screen{ screen }
            , frameRect(frameRect)
        {}

        void FrameCapturer::set(Mode::CaptureMode newCaptureMode)
        {
            captureMode = newCaptureMode;
        }

        void FrameCapturer::attachToNewWindow(HWND newWindowHandle)
        {
            windowHandle = newWindowHandle;
        }

        void FrameCapturer::newFrame()
        {
            newFrame(frameRect);
        }

        void FrameCapturer::newFrame(const boost::optional<Rect> &rect)
        {
            if (captureMode == Mode::CaptureMode::OnlyCovered)
                screenCapturerCovered.captureWindow(windowHandle, screen, frameRect);
            else
                screenCapturerNotCovered.captureWindow(windowHandle, screen, frameRect);
        }
    }
}
