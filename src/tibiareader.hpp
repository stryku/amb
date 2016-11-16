#pragma once

#include "screencapturer.hpp"
#include "tibiascreenreader.hpp"
#include "config/layout/HealthHeartConfig.hpp"
#include "capture/CoveredWindowCapturer.hpp"
#include "capture/NotCoveredWindowCapturer.hpp"
#include "capture/WindowCapturer.hpp"
#include "screencapturer.hpp"

#include <boost/variant.hpp>

#include <cassert>

#include <QtDebug>

#include <Windows.h>

namespace AMB
{
    namespace Readers
    {
        namespace details
        {
            class TibiaReader
            {
            public:
                TibiaReader(HWND tibiaWindowHandle = NULL)
                    : reader{ screen, heartLayoutConfig }
                    , screenCapturerDziala{ screen }
                    , tibiaWindowHandle{ tibiaWindowHandle }
                {}

                size_t getHpPercent()
                {
                    return reader.getHpPercent();
                }

                size_t getManaPercent()
                {
                    return reader.getManaPercent();
                }

                void newFrame()
                {
                    assert(tibiaWindowHandle != NULL);

                    if(isTibia11Mode)
                        screenCapturerNotCovered.captureWindow(tibiaWindowHandle, screen);
                    else
                        screenCapturerCovered.captureWindow(tibiaWindowHandle, screen);

                    if (screen.w == 0 && screen.h == 0)
                        throw std::exception{ "Tibia window is minimalized!" };
                }

                bool isVisible() const
                {
                    screen.toCb();
                    return reader.isHearthVisible();
                }

                void attachToNewWindow(HWND hwnd)
                {
                    tibiaWindowHandle = hwnd;
                }

                bool refindHeart()
                {
                    return reader.findHeart();
                }

                void setCaptureMode(bool tibia11 = false)
                {
                    isTibia11Mode = tibia11;
                }

            private:
                using CoveredWndCapturer = AMB::Capture::WindowCapturer<AMB::Capture::CoveredWindowCapturer>;
                using NotCoveredWndCapturer = AMB::Capture::WindowCapturer<AMB::Capture::NotCoveredWindowCapturer>;

                Layout::HealthHeartConfig heartLayoutConfig;
                Graphics::Image screen;
                TibiaScreenReader reader;
                AMB::Readers::details::ScreenCapturer screenCapturerDziala;

                NotCoveredWndCapturer screenCapturerNotCovered;
                CoveredWndCapturer screenCapturerCovered;

                HWND tibiaWindowHandle;
                bool isTibia11Mode{ false };
            };
        }
    }
}
