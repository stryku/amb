#include "Healer.hpp"

namespace AMB
{
    namespace Modules
    {
        namespace Heal
        {
            void Healer::executeRule( const HealRule &rule )
            {
                simulator.hotkey( rule.hotkey,
                                  { sleepMin, sleepMax } );
            }

            void Healer::runDetails()
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

            Healer::Healer( const Configs::HealerConfig &config,
                    Memory::TibiaStuffReader &tibiaReader,
                    Simulate::Simulator &simulator ) :
                Module( tibiaReader, simulator ),
                config( config )
            {}
        }
    }
}
