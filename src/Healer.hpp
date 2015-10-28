#pragma once

#include "HealRule.hpp"
#include "Module.hpp"
#include "TibiaStuffReader.hpp"
#include "Simulator.hpp"

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
                static const size_t sleepMin = 400;
                static const size_t sleepMax = 600;

                const Configs::HealerConfig &config;

                void executeRule( const HealRule &rule );

                void runDetails();

            public:
                Healer( const Configs::HealerConfig &config,
                        Memory::TibiaStuffReader &tibiaReader,
                        Simulate::Simulator &simulator );
                ~Healer()
                {}


            };
        }
    }
}
