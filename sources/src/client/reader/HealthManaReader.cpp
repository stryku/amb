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
                LOG_DEBUG("HealthManaReader reading hp");
                return getPercent(barsConfig.health, lastCapturedRect);
            }

            size_t HealthManaReader::getManaPercent(const RelativeRect &lastCapturedRect) const
            {
                LOG_DEBUG("HealthManaReader reading mana");
                return getPercent(barsConfig.mana, lastCapturedRect);
            }

            size_t HealthManaReader::getPercent(const Config::Layout::HealthManaBars::BarConfig &config, const RelativeRect &lastCapturedRect) const
            {
                LOG_DEBUG("HealthManaReader reading pixels. Config:");
                LOG_DEBUG("first pixel: r = %d, g = %d, b = %d", config.firstPixel.r, config.firstPixel.g, config.firstPixel.b);
                LOG_DEBUG("other pixel: r = %d, g = %d, b = %d", config.otherPixels.r, config.otherPixels.g, config.otherPixels.b);
                LOG_DEBUG("offset from hearth: x = %d, y = %d", config.offsetFromHeart.x, config.offsetFromHeart.y);
                LOG_DEBUG("max len = %d", config.maxLength);

                auto rect = heartLayoutConfig_2.rect.relativeToRect(lastCapturedRect);
                size_t px{ 0 };
                const Pos base{ config.offsetFromHeart.x + rect.x,
                                config.offsetFromHeart.y + rect.y };

                LOG_DEBUG("base: x = %d, y = %d", base.x, base.y);

                if (screen.cpixel(base.x, base.y) != config.firstPixel)
                {
                    LOG_DEBUG("first pixel doesn't match, returning 0");
                    return 0;
                }

                ++px;

                while (screen.cpixel(base.x + px, base.y) == config.otherPixels && px < config.maxLength)
                    ++px;

                LOG_DEBUG("Returning bar pixels: %d", px);
                return px;
            }

            bool HealthManaReader::findHeart(const RelativeRect &lastCapturedRect)
            {
                //heartLayoutConfig_2.rect.relationPoint = lastCapturedRect.relationPoint;
                //auto rect = heartLayoutConfig_2.rect.relativeToRect(lastCapturedRect);
                ////const auto x = screen.w - heartLayoutConfig.offsetFromRight - 1;
                //screen.toCb();

                //LOG_DEBUG("TibiaScreenReader refinding heart. Before: %d, %d", heartLayoutConfig_2.rect.rect.x, heartLayoutConfig_2.rect.rect.y);

                //for (rect.y = 0; 
                //     static_cast<size_t>(rect.y) < screen.h - heartLayoutConfig_2.rect.rect.h; 
                //     ++rect.y)
                //{
                //    if (screen.getSprite(rect) == heartLayoutConfig_2.pixels)
                //    {
                //        heartLayoutConfig_2.rect.rect.y = rect.y;
                //        LOG_DEBUG("TibiaScreenReader heart found: %d, %d", heartLayoutConfig_2.rect.rect.x, heartLayoutConfig_2.rect.rect.y);
                //        return true;
                //    }
                //}

                //LOG_DEBUG("TibiaScreenReader heart NOT found!");
                //return false;
            }

            void HealthManaReader::setTibiaClientType(Client::TibiaClientType clientType)
            {
                LOG_DEBUG("HealthManaReader setting client type: %d", Client::toSize_t(clientType));

                //heartLayoutConfig = Config::Layout::HealthHeart::Factory{}.create(clientType);
                heartLayoutConfig_2 = Config::Layout::HealthHeart::Factory{}.create_2(clientType);
                //heartLayoutConfig_11_big = heartLayoutConfig_2;
                //heartLayoutConfig_11_big.pixels = Config::Layout::HealthHeart::Static::pixels_big;
                //heartLayoutConfig_11_big.rect.rect.x = -static_cast<int>(Config::Layout::HealthHeart::Static::offsetFromRight_11_big);
                barsConfig = Config::Layout::HealthManaBars::Factory{}.create(clientType);
            }

            bool HealthManaReader::isVisible(const RelativeRect &lastCapturedRect) const
            {
                auto heartLayout = heartLayoutConfig_2;
                heartLayout.rect.relationPoint = lastCapturedRect.relationPoint;
                const auto rect = heartLayout.rect.relativeToRect(lastCapturedRect);

                LOG_DEBUG("HealthManaReader isVisible. Checking heart at rect:");
                LOG_DEBUG_RECT(rect);

                const auto ret = screen.getSprite(rect) == heartLayoutConfig_2.pixels;
            
                LOG_DEBUG("HealthManaReader isVisible retutning: %d", static_cast<int>(ret));

                return ret;
            }
        }
    }
}
