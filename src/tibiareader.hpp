#pragma once

#include "screencapturer.hpp"
#include "tibiascreenreader.hpp"
#include "config/layout/HealthHeartConfig.hpp"

#include <cassert>

#include <QtDebug>

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
                    , screenCapturer{ screen }
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
                    screenCapturer.recapture(tibiaWindowHandle);
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

            private:
                Layout::HealthHeartConfig heartLayoutConfig;
                Graphics::Image screen;
                TibiaScreenReader reader;
                ScreenCapturer screenCapturer;
                HWND tibiaWindowHandle;
            };
        }
    }
}
