#include "capture/FrameCapturer.hpp"
#include "graphics/Image.hpp"
#include "client/TibiaClientWindowInfo.hpp"

namespace Amb
{
    namespace Capture
    {
        FrameCapturer::FrameCapturer(Graphics::Image &screen, const Client::TibiaClientWindowInfo &clientInfo)
            : screen{ screen }
            , clientInfo{ clientInfo }
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
                screenCapturerCovered.captureWindow(windowHandle, clientInfo.rect, screen, rect);
            else
                screenCapturerNotCovered.captureWindow(windowHandle, clientInfo.rectOnMonitors, screen, rect);

            screen.toCb();
        }
    }
}
