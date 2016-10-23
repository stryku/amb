#pragma once

#include "screencapturer.hpp"
#include "utils/Structs.hpp"
#include "config/layout/HealthHeartConfig.hpp"
#include "graphics/Image.hpp"

#include <QtDebug>

namespace AMB
{
    namespace Readers
    {
        namespace details
        {
            class TibiaScreenReader
            {
            public:
                TibiaScreenReader(const Graphics::Image &screen,
                                  const Layout::HealthHeartConfig &heartConfig)
                    : screen{ screen }
                    , heartConfig{ heartConfig }
                {}

                size_t getHpPercent() const
                {
                    qDebug("TibiaScreenReader Reading hp\n");
                    return getPercent(hpInfo);
                }

                size_t getManaPercent() const
                {
                    return getPercent(manaInfo);
                }

                size_t isHearthVisible() const
                {
                    return screen.getSprite(heartConfig.pos.x, 
                                            heartConfig.pos.y,
                                            Layout::HealthHeartConfig::size.w, 
                                            Layout::HealthHeartConfig::size.h) == heartConfig.pixels;
                }

            private:
                struct HpManaInfo
                {
                    Rgba firstPixel;
                    Rgba otherPixels;
                    Pos pos;

                    static const size_t MaxLength = 1303 - 1216;
                };

                size_t getPercent(const HpManaInfo &info) const
                {
                    size_t px{ 0 };

                    if (screen.cpixel(info.pos.x, info.pos.y) != info.firstPixel)
                        return 0;

                    ++px;

                    while (screen.cpixel(info.pos.x + px, info.pos.y) == info.otherPixels && px < HpManaInfo::MaxLength)
                        ++px;

                    return px;
                }

                const HpManaInfo hpInfo = { Rgba{ 79, 79, 211, 255 }, Rgba{ 79, 79, 219, 255 }, Pos{ 1217, 153 } };
                const HpManaInfo manaInfo = { Rgba{ 211, 79, 82, 255 }, Rgba{ 218, 80, 83, 255 }, Pos{ 1217, 166} };
                const Graphics::Image &screen;
                const Layout::HealthHeartConfig &heartConfig;
            };
        }
    }
}
