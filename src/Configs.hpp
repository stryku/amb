#pragma once

#include "utils.hpp"
#include "ui/modules/healer/HealRule.hpp"
#include "utils/Structs.hpp"
#include "utils/PropertyTreeBuilder.hpp"

#include "ui/modules/looter/Category.hpp"
#include "ui/modules/looter/LootItem.hpp"
#include "capture/CaptureMode.hpp"

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

            struct
            {
                Capture::Mode captureMode;
            } common;

            void toPropertyTreeBuilder(Utils::PropertyTreeBuilder &builder, const std::string &path = "") const
            {
                healer.randBetweenChecks.toPropertyTreeBuilder(builder, path + ".healer.rand_between_checks");
                healer.randBetweenChecks.toPropertyTreeBuilder(builder, path + ".healer.sleep_after_hotkey");
                common.captureMode.toPropertyTreeBuilder(builder, path + ".common");
            }

            static AdvancedSettings fromPtree(boost::property_tree::ptree &tree)
            {
                AdvancedSettings ret;

                ret.healer.randBetweenChecks = FromTo::fromPtree(tree.get_child("healer.rand_between_checks"));
                ret.healer.sleepAfterHotkey = FromTo::fromPtree(tree.get_child("healer.sleep_after_hotkey"));

                ret.common.captureMode = Capture::Mode::fromPtree(tree.get_child("common"));

                return ret;
            }
        };

        struct Looter
        {
            std::vector<AMB::Ui::Modules::Looter::Category> categories;
            std::vector<AMB::Ui::Modules::Looter::LootItem> items;

            auto toPtree() const
            {
                Utils::PropertyTreeBuilder builder;

                if (categories.empty())
                    builder.addElement(Utils::PtreeElement<>{"categories", ""});
                else
                {
                    for (const auto& category : categories)
                    {
                        auto tree = category.toPtree();
                        builder.addTree("categories.category", tree);
                    }
                }

                if (items.empty())
                    builder.addElement(Utils::PtreeElement<>{"items", ""});
                else
                {
                    for (const auto& item : items)
                    {
                        auto tree = item.toPtree();
                        builder.addTree("items.item", tree);
                    }
                }

                return builder.buildTree();
            }

            static Looter fromPtree(boost::property_tree::ptree &tree)
            {
                Looter healer;

                for (auto &child : tree.get_child("categories"))
                {
                    const auto cat = AMB::Ui::Modules::Looter::Category::fromPtree(child.second);
                    healer.categories.emplace_back(cat);
                }

                for (auto &child : tree.get_child("items"))
                {
                    const auto rule = AMB::Ui::Modules::Looter::LootItem::fromPtree(child.second);
                    healer.items.emplace_back(rule);
                }

                return healer;
            }
        };

        struct GlobalConfig
        {
            DWORD pid;
            HWND hwnd;
            HealerConfig healerConfig;
            AdvancedSettings advancedSettings;
            Looter looter;

            std::string toString() const
            {
                Utils::PropertyTreeBuilder builder;

                builder.addElement(Utils::PtreeElement<>{"amb.version", "0.0.1"});
                
                builder.addTree("amb.healer_config", healerConfig.toPtree());
                advancedSettings.toPropertyTreeBuilder(builder, "amb.advanced_settings");
                builder.addTree("amb.looter", looter.toPtree());

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
                ret.looter = Looter::fromPtree(tree.get_child("amb.looter"));

                return ret;
            }
        };
    };
}
