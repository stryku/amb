#pragma once

#include "config/layout/health_heart/HealthHeartConfig.hpp"
#include "client/TibiaClientType.hpp"
#include "graphics/Image.hpp"
#include "config/layout/health_heart/HealthHeartConfigFactory.hpp"

namespace Amb
{
    namespace Client
    {
        namespace Finder
        {
            class HealthManaFinder
            {
            public:
                HealthManaFinder(const Graphics::Image &screen)
                    : screen{ screen }
                {}

                boost::optional<Config::Layout::HealthHeart::HealthHeartBasicConfig> find(TibiaClientType clientType,
                                                                                          const RelativeRect &lastCapturedRect)
                {
                    Config::Layout::HealthHeart::HealthHeartBasicConfig config;
                    Rect rect = getBasicRect(clientType);

                    for (rect.y = 0;
                         static_cast<size_t>(rect.y) < screen.h - 50;
                         ++rect.y)
                    {
                        if (screen.getSprite(rect) == Config::Layout::HealthHeart::Static::pixels)
                        {
                            config.pos.y = rect.y;
                            config.pos.x = rect.x - screen.w;
                            config.isSmall = true;
                            return config;
                        }
                    }

                    return {};
                }

                boost::optional<Config::Layout::HealthHeart::HealthHeartBasicConfig> findBruteForce(TibiaClientType clientType,
                                                                                                    const RelativeRect &lastCapturedRect)
                {
                    Config::Layout::HealthHeart::HealthHeartBasicConfig config;
                    Rect rect = getBasicRect(clientType);

                    for (; rect.x > screen.w / 2; --rect.x)
                    {
                        for (rect.y = 0;
                             static_cast<size_t>(rect.y) < screen.h - 50;
                             ++rect.y)
                        {
                            const auto sprite = screen.getSprite(rect);

                            if (sprite == Config::Layout::HealthHeart::Static::pixels)
                            {
                                config.pos.y = rect.y;
                                config.pos.x = rect.x - screen.w;
                                config.isSmall = true;
                                return config;
                            }

                            if (sprite == Config::Layout::HealthHeart::Static::pixels_big)
                            {
                                config.pos.y = rect.y;
                                config.pos.x = rect.x - screen.w;
                                config.isSmall = false;
                                return config;
                            }
                        }
                    }

                    return{};
                }

            private:
                Rect getBasicRect(TibiaClientType clientType) const
                {
                    Rect rect;

                    rect.w = Config::Layout::HealthHeart::Static::size.w;
                    rect.h = Config::Layout::HealthHeart::Static::size.h;

                    rect.y = 0;

                    switch (clientType)
                    {
                    case Amb::Client::TibiaClientType::Tibia10:
                        rect.x = -static_cast<int>(Config::Layout::HealthHeart::Static::offsetFromRight_10);
                        break;

                    case Amb::Client::TibiaClientType::Tibia11:
                        rect.x = -static_cast<int>(Config::Layout::HealthHeart::Static::offsetFromRight_11);
                        break;

                    case Amb::Client::TibiaClientType::Flash:
                    default:
                        assert(false);
                    }

                    return rect;
                }

                const Graphics::Image &screen;
            };
        }
    }
}
