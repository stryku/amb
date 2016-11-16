#pragma once

#include "screencapturer.hpp"
#include "tibiascreenreader.hpp"
#include "config/layout/HealthHeartConfig.hpp"
#include "capture/DeadCreatureWindowFinder.hpp"
#include "db/Items.hpp"
#include "capture/ItemsWindowReader.hpp"
#include "capture/CoveredWindowCapturer.hpp"
#include "capture/NotCoveredWindowCapturer.hpp"
#include "capture/WindowCapturer.hpp"
#include "screencapturer.hpp"

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
                TibiaReader(const Db::Items &itemsDb, HWND tibiaWindowHandle = NULL)
                    : reader{ screen, heartLayoutConfig }
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

                auto getDeadCreaturesWindows() const
                {
                    return deadCreatureWindowsFinder.find();
                }

                auto readItemWindow(const Pos &pos) const
                {
                    return itemsWindowReader.read(pos);
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
                Capture::DeadCreatureWindowFinder deadCreatureWindowsFinder;
                Capture::ItemsWindowReader itemsWindowReader;

                NotCoveredWndCapturer screenCapturerNotCovered;
                CoveredWndCapturer screenCapturerCovered;

                HWND tibiaWindowHandle;
                bool isTibia11Mode{ true };
            };
        }
    }
}
