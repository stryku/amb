#pragma once

namespace Amb
{
    namespace Config
    {
        namespace Layout
        {
            namespace HealthHeart
            {
                struct HealthHeartConfig;
            }

            namespace HealthManaBars
            {
                struct BarConfig;
            }
        }
    }
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
                HealthManaReader(const Graphics::Image &screen,
                                 Amb::Config::Layout::HealthHeart::HealthHeartConfig &heartConfig);

                size_t getHpPercent() const;
                size_t getManaPercent() const;
                bool findHeart();

            private:
                size_t getPercent(const Config::Layout::HealthManaBars::BarConfig &config) const;

                const Graphics::Image &screen;
                Amb::Config::Layout::HealthHeart::HealthHeartConfig &heartConfig;
                Amb::Config::Layout::HealthManaBars::BarsConfig barsConfig;
            };
        }
    }
}
