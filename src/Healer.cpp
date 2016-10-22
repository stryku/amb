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
                std::cout<<"siema\n";

                auto sleepTo = std::chrono::system_clock::now() +
                               std::chrono::milliseconds( Utils::RandomBetween{ sleepMin, sleepMax }.get() );

                reader.newFrame();

                for( const auto &rule : config.rules )
                {
                    if(reader.isVisible())
                    {
                        auto hp = reader.getHpPercent();
                        auto mana = reader.getManaPercent();

                        std::cout<<"hp: "<<hp<<", mana: "<<mana<<"\n";

                        if( rule.passed( hp, mana ) )
                        {
                            std::cout<<"rule passed\n";
                            executeRule( rule );
                        }
                    }
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
