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
            }
        }
    }
}
