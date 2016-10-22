#pragma once

#include "HealRule.hpp"
#include "Module.hpp"
#include "Simulator.hpp"
#include "tibiareader.hpp"

#include <chrono>

namespace AMB
{
    namespace Modules
    {
        namespace Heal
        {
            class Healer : public Module
            {
            private:
                static const size_t sleepMin = 100;
                static const size_t sleepMax = 450;

                Readers::details::TibiaReader reader;

                const Configs::HealerConfig &config;

                void executeRule( const HealRule &rule );

                void runDetails();

            public:
                Healer( const Configs::HealerConfig &config,
                        Simulate::Simulator &simulator );
                ~Healer()
                {}


            };
        }
    }
}
