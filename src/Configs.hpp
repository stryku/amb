#pragma once

#include "utils.hpp"
#include "HealRule.hpp"
#include "utils/Structs.hpp"
#include "utils/PropertyTreeBuilder.hpp"

#include <vector>
#include <iostream>

namespace AMB
{
    namespace Configs
    {
        struct HealerConfig
        {
            std::vector<Modules::Heal::HealRule> rules;

            void toPropertyTreeBuilder(Utils::PropertyTreeBuilder &builder, const std::string &path = "") const
            {
                builder.addElement(Utils::PtreeElement<>{path + ".heal_rules", ""});

                for (const auto& rule : rules)
                    rule.toPropertyTreeBuilder(builder, path + ".heal_rule");
            }
        };

        struct AdvancedSettings
        {
            struct
            {
                FromTo randBetweenChecks;
                FromTo sleepAfterHotkey;
            } healer;

            void toPropertyTreeBuilder(Utils::PropertyTreeBuilder &builder, const std::string &path = "") const
            {
                healer.randBetweenChecks.toPropertyTreeBuilder(builder, path + ".healer.rand_between_checks");
                healer.randBetweenChecks.toPropertyTreeBuilder(builder, path + ".healer.sleep_after_hotkey");
            }
        };

        struct GlobalConfig
        {
            DWORD pid;
            HWND hwnd;
            HealerConfig healerConfig;
            AdvancedSettings advancedSettings;

            std::string toString() const
            {
                Utils::PropertyTreeBuilder builder;

                builder.addElement(Utils::PtreeElement<>{"amb.version", "0.0.1"});
                
                healerConfig.toPropertyTreeBuilder(builder, "amb.healer_config");
                advancedSettings.toPropertyTreeBuilder(builder, "amb.advanced_settings");

                return builder.build();
            }
        };
    };
}
