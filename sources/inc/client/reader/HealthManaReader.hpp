#pragma once

#include "client/TibiaClientType.hpp"
#include "config/layout/health_heart/HealthHeartConfig.hpp"
#include "config/layout/health_mana_bars/HealthManaBars.hpp"

namespace Amb
{
    namespace Graphics
    {
        struct Image;
    }

    namespace Client
    {
        namespace Reader
        {
            class HealthManaReader
            {
            public:
                HealthManaReader(const Graphics::Image &screen);

                size_t getHpPercent(const RelativeRect &lastCapturedRect) const;
                size_t getManaPercent(const RelativeRect &lastCapturedRect) const;
                bool isVisible(const RelativeRect &lastCapturedRect) const;
                bool findHeart(const RelativeRect &lastCapturedRect);

                void setTibiaClientType(Client::TibiaClientType clientType);
                void setHeartConfig(const Config::Layout::HealthHeart::HealthHeartConfig_2& config)
                {
                    heartLayoutConfig_2 = config;
                }


            private:
                size_t getPercent(const Config::Layout::HealthManaBars::BarConfig &config, const RelativeRect &lastCapturedRect) const;

                const Graphics::Image &screen;
                //Amb::Config::Layout::HealthHeart::HealthHeartConfig heartLayoutConfig;
                Amb::Config::Layout::HealthHeart::HealthHeartConfig_2 heartLayoutConfig_2;
                //Amb::Config::Layout::HealthHeart::HealthHeartConfig_2 heartLayoutConfig_11_big;
                Amb::Config::Layout::HealthManaBars::BarsConfig barsConfig;
            };
        }
    }
}
