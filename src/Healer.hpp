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

                Configs::HealerConfig config;

                void executeRule( const HealRule &rule )
                {
                    simulator.hotkey( rule.hotkey,
                                      { sleepMin, sleepMax } );
                }

                void initConfig()
                {
                    config.fromUi();
                }

                void runDetails()
                {
                    auto hp = tibiaReader.hp();
                    auto mana = tibiaReader.mana();

                    auto sleepTo = std::chrono::system_clock::now() +
                                   std::chrono::milliseconds( Utils::RandomBetween{ sleepMin, sleepMax }.get() );

                    for( const auto &rule : config.rules )
                    {
                        if( rule.passed( tibiaReader.hp(), tibiaReader.mana() ) )
                            executeRule( rule );
                    }

                    std::this_thread::sleep_until( sleepTo );
                }

            public:
                Healer( Memory::TibiaStuffReader &tibiaReader,
                        Simulate::Simulator &simulator ) :
                    Module( tibiaReader, simulator )
                {}
                ~Healer()
                {}


            };
        }
    }
}