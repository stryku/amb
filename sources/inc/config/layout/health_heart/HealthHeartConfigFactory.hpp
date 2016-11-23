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

                class Factory
                {
                public:
                    HealthHeartConfig create(Amb::Client::TibiaClientType clientType) const;
                };
            }
        }
    }
}
