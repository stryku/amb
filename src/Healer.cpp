#include "Healer.hpp"

#include "capture/DeadCreatureWindowFinder.hpp"

namespace AMB
{
    namespace Modules
    {
        namespace Heal
        {
            void Healer::executeRule(const AMB::Modules::Heal::HealRule &rule)
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

                auto windows = reader.getDeadCreaturesWindows();

                if (!windows.empty())
                {
                    int a = 22;
                    a += 2;

                    auto items = reader.readItemWindow(windows[0]);
                    a += 2;

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
