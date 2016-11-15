#pragma once

#include "screencapturer.hpp"
#include "tibiascreenreader.hpp"
#include "config/layout/HealthHeartConfig.hpp"
#include "capture/DeadCreatureWindowFinder.hpp"
#include "db/Items.hpp"
#include "capture/ItemsWindowReader.hpp"

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
                TibiaReader(const Db::Items &itemsDb, HWND tibiaWindowHandle = NULL)
                    : reader{ screen, heartLayoutConfig }
                    , screenCapturer{ screen }
                    , deadCreatureWindowsFinder{ screen }
                    , itemsWindowReader{ screen, itemsDb }
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

                auto getDeadCreaturesWindows() const
                {
                    return deadCreatureWindowsFinder.find();
                }

                auto readItemWindow(const Pos &pos) const
                {
                    return itemsWindowReader.read(pos);
                }

            private:
                Layout::HealthHeartConfig heartLayoutConfig;
                Graphics::Image screen;
                TibiaScreenReader reader;
                Capture::DeadCreatureWindowFinder deadCreatureWindowsFinder;
                Capture::ItemsWindowReader itemsWindowReader;
                ScreenCapturer screenCapturer;
                HWND tibiaWindowHandle;
            };
        }
    }
}
