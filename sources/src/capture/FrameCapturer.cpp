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

        void FrameCapturer::captureRightStrip()
        {
            const int offsetFromRight = 176;
            RelativeRect captureRect;
            captureRect.relationPoint = clientInfo.corners.topRight;
            captureRect.rect.x = -offsetFromRight;
            captureRect.rect.y = 0;
            captureRect.rect.w = offsetFromRight;
            captureRect.rect.h = clientInfo.rect.h;

            newFrame(captureRect.relativeToPoint(Pos{ 0,0 }));
            lastCaptureRect = captureRect;
        }

        const RelativeRect& FrameCapturer::getLastCaptureRect() const
        {
            return lastCaptureRect;
        }

    }
}
