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
                    qDebug("Reading hp\n");
                    return reader.getHpPercent();
                }

                size_t getManaPercent()
                {
                    qDebug("Reading mana\n");
                    return reader.getManaPercent();
                }

                void newFrame()
                {
                    assert(tibiaWindowHandle != NULL);
                    screenCapturer.recapture(tibiaWindowHandle);
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

            private:
                const Layout::HealthHeartConfig heartLayoutConfig;
                Graphics::Image screen;
                TibiaScreenReader reader;
                ScreenCapturer screenCapturer;
                HWND tibiaWindowHandle;
            };
        }
    }
}
