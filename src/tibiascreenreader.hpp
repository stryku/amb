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
                                  Layout::HealthHeartConfig &heartConfig)
                    : screen{ screen }
                    , heartConfig{ heartConfig }
                {}

                size_t getHpPercent() const
                {
                    return getPercent(hpInfo);
                }

                size_t getManaPercent() const
                {
                    return getPercent(manaInfo);
                }

                size_t isHearthVisible() const
                {
                    const auto x = screen.w - Layout::HealthHeartConfig::offsetFromRight_11 - 1;
                    return screen.getSprite(x,
                                            heartConfig.y,
                                            Layout::HealthHeartConfig::size.w, 
                                            Layout::HealthHeartConfig::size.h) == heartConfig.pixels;
                }

                bool findHeart()
                {
                    const auto x = screen.w - Layout::HealthHeartConfig::offsetFromRight_11 - 1;

                    qDebug("TibiaScreenReader refinding heart. Before: %d, %d", x, heartConfig.y);

                    for (size_t y = 0; y < screen.h - heartConfig.size.h; ++y)
                    {
                        if (screen.getSprite(x, y,
                                             Layout::HealthHeartConfig::size.w,
                                             Layout::HealthHeartConfig::size.h) == heartConfig.pixels)
                        {
                            heartConfig.y = y;
                            qDebug("TibiaScreenReader heart found: %d, %d", x, heartConfig.y);
                            return true;
                        }
                    }

                    qDebug("TibiaScreenReader heart NOT found!");
                    return false;
                }

            private:
                struct HpManaInfo
                {
                    Rgba firstPixel;
                    Rgba otherPixels;
                    size_t offsetFromHeartY;

                    static constexpr size_t MaxLength = 87;
                    static constexpr size_t OffsetFromHeartX = 17;
                };

                size_t getPercent(const HpManaInfo &info) const
                {
                    size_t px{ 0 };
                    const Pos base{ info.OffsetFromHeartX + screen.w - Layout::HealthHeartConfig::offsetFromRight - 1,
                                    info.offsetFromHeartY + heartConfig.y };

                    if (screen.cpixel(base.x, base.y) != info.firstPixel)
                        return 0;

                    ++px;

                    while (screen.cpixel(base.x + px, base.y) == info.otherPixels && px < HpManaInfo::MaxLength)
                        ++px;

                    return px;
                }

                static constexpr HpManaInfo hpInfo = { Rgba{ 79, 79, 211, 255 }, Rgba{ 79, 79, 219, 255 }, 4 };
                static constexpr HpManaInfo manaInfo = { Rgba{ 211, 79, 82, 255 }, Rgba{ 218, 80, 83, 255 }, 17 };
                const Graphics::Image &screen;
                Layout::HealthHeartConfig &heartConfig;
            };
        }
    }
}
