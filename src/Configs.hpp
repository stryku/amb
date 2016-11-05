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
                if (rules.empty())
                {
                    builder.addElement(Utils::PtreeElement<>{path + ".heal_rules", ""});
                    return;
                }

                for (const auto& rule : rules)
                    rule.toPropertyTreeBuilder(builder, path + ".heal_rules.heal_rule");
            }

            auto toPtree() const
            {
                Utils::PropertyTreeBuilder builder;

                if (rules.empty())
                    return builder.addElement(Utils::PtreeElement<>{"heal_rules", ""}).buildTree();

                for (const auto& rule : rules)
                {
                    auto tree = rule.toPtree();
                    builder.addTree("heal_rules.heal_rule", tree);
                }

                return builder.buildTree();
            }

            static HealerConfig fromPtree(boost::property_tree::ptree &tree)
            {
                HealerConfig healer;

                for (auto &child : tree.get_child("heal_rules"))
                {
                    const auto rule = Modules::Heal::HealRule::fromPtree(child.second);
                    healer.rules.emplace_back(rule);
                }

                return healer;
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

            static AdvancedSettings fromPtree(boost::property_tree::ptree &tree)
            {
                AdvancedSettings ret;

                ret.healer.randBetweenChecks = FromTo::fromPtree(tree.get_child("healer.rand_between_checks"));
                ret.healer.sleepAfterHotkey = FromTo::fromPtree(tree.get_child("healer.sleep_after_hotkey"));

                return ret;
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
                
                builder.addTree("amb.healer_config", healerConfig.toPtree());
                advancedSettings.toPropertyTreeBuilder(builder, "amb.advanced_settings");

                return builder.build();
            }

            static GlobalConfig fromString(const std::string &str)
            {
                GlobalConfig ret;

                boost::property_tree::ptree tree;
                std::istringstream iss(str);
                boost::property_tree::xml_parser::read_xml(iss, tree);

                ret.healerConfig = HealerConfig::fromPtree(tree.get_child("amb.healer_config"));
                ret.advancedSettings = AdvancedSettings::fromPtree(tree.get_child("amb.advanced_settings"));

                return ret;
            }
        };
    };
}
