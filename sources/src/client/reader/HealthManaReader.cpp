#include "client/reader/HealthManaReader.hpp"

#include "graphics/Image.hpp"
#include "config/layout/health_heart/HealthHeartConfig.hpp"
#include "config/layout/health_mana_bars/HealthManaBars.hpp"

#include <QDebug>

namespace Amb
{
    namespace Client
    {
        namespace Reader
        {
            HealthManaReader::HealthManaReader(const Graphics::Image &screen,
                                               Config::Layout::HealthHeart::HealthHeartConfig &heartConfig)
                : screen{ screen }
                , heartConfig{ heartConfig }
            {}


            size_t HealthManaReader::getHpPercent() const
            {
                return getPercent(barsConfig.health);
            }

            size_t HealthManaReader::getManaPercent() const
            {
                return getPercent(barsConfig.mana);
            }

            size_t HealthManaReader::getPercent(const Config::Layout::HealthManaBars::BarConfig &config) const
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

            bool HealthManaReader::findHeart()
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
        }
    }
}
