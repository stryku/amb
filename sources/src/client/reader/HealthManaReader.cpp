#include "client/reader/HealthManaReader.hpp"
#include "graphics/Image.hpp"
#include "config/layout/health_heart/HealthHeartConfig.hpp"
#include "config/layout/health_mana_bars/HealthManaBars.hpp"
#include "config/layout/health_heart/HealthHeartConfigFactory.hpp"
#include "config/layout/health_mana_bars/HealthManaBarsConfigFactory.hpp"
#include "log/log.hpp"

#include <QDebug>

namespace Amb
{
    namespace Client
    {
        namespace Reader
        {
            HealthManaReader::HealthManaReader(const Graphics::Image &screen)
                : screen{ screen }
            {}

            size_t HealthManaReader::getHpPercent(const RelativeRect &lastCapturedRect) const
            {
                return getPercent(barsConfig.health, lastCapturedRect);
            }

            size_t HealthManaReader::getManaPercent(const RelativeRect &lastCapturedRect) const
            {
                return getPercent(barsConfig.mana, lastCapturedRect);
            }

            size_t HealthManaReader::getPercent(const Config::Layout::HealthManaBars::BarConfig &config, const RelativeRect &lastCapturedRect) const
            {
                auto rect = heartLayoutConfig_2.rect.relativeToRect(lastCapturedRect);
                //const Pos base_2{ }
                size_t px{ 0 };
                const Pos base{ config.offsetFromHeart.x + rect.x,
                    config.offsetFromHeart.y + rect.y };

                if (screen.cpixel(base.x, base.y) != config.firstPixel)
                    return 0;

                ++px;

                while (screen.cpixel(base.x + px, base.y) == config.otherPixels && px < config.maxLength)
                    ++px;

                return px;
            }

            bool HealthManaReader::findHeart(const RelativeRect &lastCapturedRect)
            {
                heartLayoutConfig_2.rect.relationPoint = lastCapturedRect.relationPoint;
                auto rect = heartLayoutConfig_2.rect.relativeToRect(lastCapturedRect);
                //const auto x = screen.w - heartLayoutConfig.offsetFromRight - 1;
                screen.toCb();

                LOG_DEBUG("TibiaScreenReader refinding heart. Before: %d, %d", heartLayoutConfig_2.rect.rect.x, heartLayoutConfig_2.rect.rect.y);

                for (rect.y = 0; rect.y < screen.h - heartLayoutConfig_2.rect.rect.h; ++rect.y)
                {
                    if (screen.getSprite(rect) == heartLayoutConfig.pixels)
                    {
                        heartLayoutConfig_2.rect.rect.y = rect.y;
                        LOG_DEBUG("TibiaScreenReader heart found: %d, %d", heartLayoutConfig_2.rect.rect.x, heartLayoutConfig_2.rect.rect.y);
                        return true;
                    }
                }

                LOG_DEBUG("TibiaScreenReader heart NOT found!");
                return false;
            }

            void HealthManaReader::setTibiaClientType(Client::TibiaClientType clientType)
            {
                heartLayoutConfig = Config::Layout::HealthHeart::Factory{}.create(clientType);
                heartLayoutConfig_2 = Config::Layout::HealthHeart::Factory{}.create_2(clientType);
                barsConfig = Config::Layout::HealthManaBars::Factory{}.create(clientType);
            }

            bool HealthManaReader::isVisible(const RelativeRect &lastCapturedRect) const
            {
                auto heartLayout = heartLayoutConfig_2;
                heartLayout.rect.relationPoint = lastCapturedRect.relationPoint;
                const auto rect = heartLayout.rect.relativeToRect(lastCapturedRect);
                return screen.getSprite(rect) == heartLayoutConfig.pixels;

                /*const auto x = lastCapturedRect.w - heartLayoutConfig.offsetFromRight - 1;
                const auto y = lastCapturedRect.
                return screen.getSprite(x,
                                        heartLayoutConfig.y,
                                        heartLayoutConfig.size.w,
                                        heartLayoutConfig.size.h) == heartLayoutConfig.pixels;*/
            }
        }
    }
}
