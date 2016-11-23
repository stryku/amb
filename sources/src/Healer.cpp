#include "module/modules/Healer.hpp"

#include "capture/DeadCreatureWindowFinder.hpp"

namespace Amb
{
    namespace Module
    {
        namespace Heal
        {
            void Healer::executeRule(const Amb::Module::Heal::HealRule &rule)
            {
                simulator.hotkey(rule.hotkey, { static_cast<size_t>(advancedSettings.healer.sleepAfterHotkey.from),
                                                static_cast<size_t>(advancedSettings.healer.sleepAfterHotkey.to) });
            }

            void Healer::runDetails()
            {
                const auto sleepTo = std::chrono::system_clock::now() +
                    std::chrono::milliseconds(Utils::RandomBetween{ static_cast<size_t>(advancedSettings.healer.randBetweenChecks.from), 
                                                                    static_cast<size_t>(advancedSettings.healer.randBetweenChecks.to) }.get());
                reader.newFrame();

                if (!reader.isVisible())
                {
                    qDebug("Heart not on its place, refinding...");
                    if (!reader.refindHeart())
                        throw std::exception("Couldn't locate health and mana status!");
                }

                auto hp = reader.getHpPercent();
                auto mana = reader.getManaPercent();

                for (const auto &rule : config.rules)
                {
                    if (rule.passed(hp, mana))
                    {
                        qDebug("Rule passed");
                        executeRule(rule);
                    }
                }

                std::this_thread::sleep_until(sleepTo);
            }

            Healer::Healer(const Configs::HealerConfig &config,
                           const Configs::AdvancedSettings &advancedSettings,
                           Simulate::Simulator &simulator)
                : ModuleCore{ simulator }
                , reader{ items }
                , config{ config }
                , advancedSettings{ advancedSettings }
            {}

            void Healer::applyConfigs()
            {
                reader.setTibiaClientType(advancedSettings.common.clientType);
            }


        }
    }
}
