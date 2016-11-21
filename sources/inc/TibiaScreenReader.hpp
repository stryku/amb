#pragma once

#include "screencapturer.hpp"
#include "utils/Structs.hpp"
#include "config/layout/health_heart/HealthHeartConfig.hpp"
#include "config/layout/health_mana_bars/HealthManaBarsConfigFactory.hpp"
#include "config/layout/health_mana_bars/HealthManaBars.hpp"

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
                                  Amb::Config::Layout::HealthHeart::HealthHeartConfig &heartConfig)
                    : screen{ screen }
                    , heartConfig{ heartConfig }
                {}

                void setTibiaClientType(Amb::Client::TibiaClientType clientType)
                {
                    barsConfig = Amb::Config::Layout::HealthManaBars::Factory{}.create(clientType);
                }

                size_t getHpPercent() const
                {
                    return getPercent(barsConfig.health);
                }

                size_t getManaPercent() const
                {
                    return getPercent(barsConfig.mana);
                }

                size_t isHearthVisible() const
                {
                    const auto x = screen.w - heartConfig.offsetFromRight - 1;
                    return screen.getSprite(x,
                                            heartConfig.y,
                                            heartConfig.size.w,
                                            heartConfig.size.h) == heartConfig.pixels;
                }

                bool findHeart()
                {
                    const auto x = screen.w - heartConfig.offsetFromRight - 1;
                    screen.toCb();

                    qDebug("TibiaScreenReader refinding heart. Before: %d, %d", x, heartConfig.y);

                    for (size_t y = 0; y < screen.h - heartConfig.size.h; ++y)
                    {
                        if (screen.getSprite(x, y,
                                             heartConfig.size.w,
                                             heartConfig.size.h) == heartConfig.pixels)
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
                /*struct HpManaInfo
                {
                    Rgba firstPixel;
                    Rgba otherPixels;
                    size_t offsetFromHeartY;

                    static constexpr size_t MaxLength = 87;
                    static constexpr size_t OffsetFromHeartX = 17;
                };*/

                size_t getPercent(const Amb::Config::Layout::HealthManaBars::BarConfig &config) const
                {
                    size_t px{ 0 };
                    const Pos base{ config.offsetFromHeart.x + screen.w - heartConfig.offsetFromRight - 1,
                        config.offsetFromHeart.y + heartConfig.y };

                    if (screen.cpixel(base.x, base.y) != config.firstPixel)
                        return 0;

                    ++px;

                    while (screen.cpixel(base.x + px, base.y) == config.otherPixels && px < config.maxLength)
                        ++px;

                    return px;
                }

                //static constexpr HpManaInfo hpInfo = { Rgba{ 79, 79, 211, 255 }, Rgba{ 79, 79, 219, 255 }, 5 };
                //static constexpr HpManaInfo manaInfo = { Rgba{ 211, 79, 82, 255 }, Rgba{ 218, 80, 83, 255 }, 18 };
                const Graphics::Image &screen;
                Amb::Config::Layout::HealthHeart::HealthHeartConfig &heartConfig;
                Amb::Config::Layout::HealthManaBars::BarsConfig barsConfig;
            };
        }
    }
}
