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
                static const size_t sleepMin = 700;
                static const size_t sleepMax = 800;

                Memory::TibiaStuffReader &tibiaReader;
                Simulate::Simulator &simulator;

                void executeRule( const HealRule &rule )
                {
                    simulator.hotkey( rule.hotkey,
                                      { sleepMin, sleepMax } );
                }

                void runDetails()
                {
                    auto hp = tibiaReader.hp();
                    auto mana = tibiaReader.mana();

                    for( const auto &rule : config.healerConfig.rules )
                    {
                        while( rule.passed( hp, mana ) )
                            executeRule( rule );
                    }
                }

            public:
                Healer( Configs::GlobalConfig &config,
                        Simulate::Simulator &simulator,
                        Memory::TibiaStuffReader &tibiaReader ) :
                    Module( config ),
                    simulator( simulator ),
                    tibiaReader( tibiaReader )
                {}
                ~Healer()
                {}


            };
        }
    }
}