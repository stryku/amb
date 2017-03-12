#pragma once

#include "utils/random/RandomBetween.hpp"
#include "client/Hotkey.hpp"

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
                                     Client::Hotkey hotkey,
                                     size_t percentFrom,
                                     size_t percentTo);

                void cast(const RelativeRect& lastCapturedRect);

            private:
                Simulate::Simulator& simulator;
                Client::Reader::HealthManaReader& healthManaReader;
                Client::Hotkey hotkey;
                Utils::Random::RandomBetween percentRand;
                size_t nextPercentToCast;
            };
        }
    }
}
