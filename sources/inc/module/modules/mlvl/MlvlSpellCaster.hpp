#pragma once

#include "utils.hpp"

#include <chrono>

namespace Amb
{
    struct RelativeRect;

    namespace Client
    {
        namespace Reader
        {
            class HealthManaReader;
        }
    }
    
    namespace Simulate
    {
        class Simulator;
    }

    namespace Module
    {
        namespace Mlvl
        {
            class SpellCaster
            {
            public:
                explicit SpellCaster(Simulate::Simulator& simulator,
                                     Client::Reader::HealthManaReader& healthManaReader,
                                     Utils::Hotkey hotkey,
                                     size_t percentFrom,
                                     size_t percentTo);

                void cast(const RelativeRect& lastCapturedRect);

            private:
                Simulate::Simulator& simulator;
                Client::Reader::HealthManaReader& healthManaReader;
                Utils::Hotkey hotkey;
                Utils::RandomBetween percentRand;
                size_t nextPercentToCast;
            };
        }
    }
}
