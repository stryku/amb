#pragma once

#include "utils/random/RandomBetween.hpp"

#include <chrono>

namespace Amb
{
    namespace Simulate
    {
        class Simulator;
    }

    namespace Module
    {
        namespace Mlvl
        {
            class AntiIdler
            {
            public:
                AntiIdler(Simulate::Simulator& simulator);

                void andiIdle();

            private:
                void randMove();

                static constexpr auto minWaitMs{ 10 * 1000 };
                static constexpr auto maxWaitMs{ 8 * 60 * 1000 };

                Simulate::Simulator& simulator;
                std::chrono::time_point<std::chrono::system_clock> nextMove;
                Utils::Random::RandomBetween waitRandom;
            };
        }
    }
}