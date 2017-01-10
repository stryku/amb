#pragma once

#include "client/TibiaClientType.hpp"

namespace Amb
{
    namespace Client
    {
        namespace Window
        {
            namespace Finder
            {
                class DeadCreatureWindowFinder;

                class DeadCreatureWindowFinderFactory
                {
                public:
                    DeadCreatureWindowFinder create(TibiaClientType clientType);
                };
            }
        }
    }
}
