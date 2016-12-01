#pragma once

#include "client/TibiaClientType.hpp"

namespace Amb
{
    namespace Config
    {
        namespace Layout
        {
            namespace HealthHeart
            {
                struct HealthHeartConfig;
                struct HealthHeartConfig_2;

                class Factory
                {
                public:
                    HealthHeartConfig create(Amb::Client::TibiaClientType clientType) const;
                    HealthHeartConfig_2 create_2(Amb::Client::TibiaClientType clientType) const;
                };
            }
        }
    }
}
