#pragma once

#include "screencapturer.hpp"
#include "tibiascreenreader.hpp"
#include "capture/DeadCreatureWindowFinder.hpp"
#include "db/Items.hpp"
#include "capture/ItemsWindowReader.hpp"
#include "capture/CoveredWindowCapturer.hpp"
#include "capture/NotCoveredWindowCapturer.hpp"
#include "capture/WindowCapturer.hpp"
#include "screencapturer.hpp"
#include "config/layout/health_heart/HealthHeartConfigFactory.hpp"

#include <cassert>

#include <QtDebug>

#include <Windows.h>

namespace Amb
{
    namespace Readers
    {
        namespace details
        {
            class TibiaReader
            {
            public:
                TibiaReader(const Db::Items &itemsDb, 
                            HWND tibiaWindowHandle = NULL)
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

                    //if(isTibia11Mode)
                        //screenCapturerNotCovered.captureWindow(tibiaWindowHandle, screen);
                    //else
                        //screenCapturerCovered.captureWindow(tibiaWindowHandle, screen);

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

                void setTibiaClientType(Amb::Client::TibiaClientType clientType)
                {
                    heartLayoutConfig = Amb::Config::Layout::HealthHeart::Factory{}.create(clientType);
                    setCaptureMode(clientType == Amb::Client::TibiaClientType::Tibia11);
                    reader.setTibiaClientType(clientType);
                }

            private:
                using CoveredWndCapturer = Amb::Capture::WindowCapturer<Amb::Capture::CoveredWindowCapturer>;
                using NotCoveredWndCapturer = Amb::Capture::WindowCapturer<Amb::Capture::NotCoveredWindowCapturer>;

                Amb::Config::Layout::HealthHeart::HealthHeartConfig heartLayoutConfig;
                Graphics::Image screen;
                TibiaScreenReader reader;
                Capture::DeadCreatureWindowFinder deadCreatureWindowsFinder;
                Capture::ItemsWindowReader itemsWindowReader;

                NotCoveredWndCapturer screenCapturerNotCovered;
                CoveredWndCapturer screenCapturerCovered;

                HWND tibiaWindowHandle;
                bool isTibia11Mode{ false };
            };
        }
    }
}
