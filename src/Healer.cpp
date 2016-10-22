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
                qDebug("Healer::runDetails");
                auto sleepTo = std::chrono::system_clock::now() +
                               std::chrono::milliseconds( Utils::RandomBetween{ sleepMin, sleepMax }.get() );

                reader.newFrame();
                if (reader.isVisible())
                {
                    auto hp = reader.getHpPercent();
                    auto mana = reader.getManaPercent();

                    qDebug("Healer: hp: %d, mana: %d", hp, mana);

                    for (const auto &rule : config.rules)
                    {
                        if (rule.passed(hp, mana))
                        {
                            qDebug("Rule passed");
                            executeRule(rule);
                        }
                    }
                }

                std::this_thread::sleep_until( sleepTo );
            }

            Healer::Healer( const Configs::HealerConfig &config,
                    Simulate::Simulator &simulator ) :
                Module( simulator ),
                config( config )
            {}
        }
    }
}
