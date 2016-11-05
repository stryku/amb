#pragma once

#include "ui/UiControls.hpp"
#include "Configs.hpp"
#include "utils/Structs.hpp"
#include "HealerRulesTable.hpp"

namespace AMB
{
    namespace Ui
    {
        namespace Updaters
        {
            class Healer
            {
            public:
                void update(const Configs::HealerConfig &healerConfigs, const Controls::Healer &healerControls)
                {
                    for (const auto &rule : healerConfigs.rules)
                        healerControls.healerRulesTable->add(rule.minHp,
                                                             rule.maxHp,
                                                             rule.minMana,
                                                             rule.maxMana,
                                                             Utils::hotkeyToSize_t(rule.hotkey));
                }
            };
        }
    }
}
