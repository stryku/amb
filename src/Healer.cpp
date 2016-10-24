#include "Healer.hpp"

namespace AMB
{
    namespace Modules
    {
        namespace Heal
        {
            void Healer::executeRule(const HealRule &rule)
            {
                simulator.hotkey(rule.hotkey, { static_cast<size_t>(advancedSettings.healer.sleepAfterHotkey.from),
                                                static_cast<size_t>(advancedSettings.healer.sleepAfterHotkey.to) });
            }

            void Healer::runDetails()
            {
                qDebug("Healer::runDetails");
                const auto sleepTo = std::chrono::system_clock::now() +
                    std::chrono::milliseconds(Utils::RandomBetween{ static_cast<size_t>(advancedSettings.healer.randBetweenChecks.from), 
                                                                    static_cast<size_t>(advancedSettings.healer.randBetweenChecks.to) }.get());

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

                std::this_thread::sleep_until(sleepTo);
            }

            Healer::Healer(const Configs::HealerConfig &config,
                           const Configs::AdvancedSettings &advancedSettings,
                           Simulate::Simulator &simulator)
                : Module{ simulator }
                , config{ config }
                , advancedSettings{ advancedSettings }
            {}
        }
    }
}
