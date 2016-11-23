#pragma once

#include "client/TibiaClientType.hpp"

namespace Amb
{
    namespace Config
    {
        namespace Layout
        {
            namespace HealthManaBars
            {
                struct BarsConfig;

                class Factory
                {
                public:
                    BarsConfig create(Amb::Client::TibiaClientType clientType) const;
                };
            }
        }
    }
}


