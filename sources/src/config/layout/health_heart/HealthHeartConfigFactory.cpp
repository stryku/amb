#include "config/layout/health_heart/HealthHeartConfigFactory.hpp"
#include "config/layout/health_heart/StaticValues.hpp"
#include "config/layout/health_heart/HealthHeartConfig.hpp"

namespace Amb
{
    struct Size;

    namespace Config
    {
        namespace Layout
        {
            namespace HealthHeart
            {
                HealthHeartConfig Factory::create(Amb::Client::TibiaClientType clientType) const
                {
                    HealthHeartConfig config{ Static::size,
                                              0,
                                              0,
                                              Static::pixels };

                    switch (clientType)
                    {
                        case Amb::Client::TibiaClientType::Tibia10: 
                            config.offsetFromRight = Static::offsetFromRight_10;
                        break;

                        case Amb::Client::TibiaClientType::Tibia11:
                            config.offsetFromRight = Static::offsetFromRight_11;
                        break;

                        case Amb::Client::TibiaClientType::Flash:
                        default:
                            assert(false);
                    }

                    return config;
                }

                HealthHeartConfig_2 Factory::create_2(Client::TibiaClientType clientType,
                                                      const HealthHeartBasicConfig& basicConfig) const
                {
                    HealthHeartConfig_2 config;
                    config.rect.rect.w = Static::size.w;
                    config.rect.rect.h = Static::size.h;
                    config.rect.rect.y = basicConfig.pos.y;
                    config.rect.rect.x = basicConfig.pos.x;

                    if (basicConfig.isSmall)
                        config.pixels = Static::pixels;
                    else
                        config.pixels = Static::pixels_big;

                    return config;
                }
            }
        }
    }
}
