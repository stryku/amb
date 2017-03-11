#pragma once

#include "utils/Observable.hpp"
#include "utils.hpp"
#include "ui/modules/healer/HealRule.hpp"
#include "utils/Structs.hpp"
#include "utils/PropertyTreeBuilder.hpp"

#include "ui/modules/looter/Category.hpp"
#include "ui/modules/looter/LootItem.hpp"
#include "capture/CaptureMode.hpp"
#include "client/TibiaClientWindowInfo.hpp"




#include "config/module/HealerConfig.hpp"



#include <boost/assert.hpp>

#include <vector>
#include <iostream>
#include "client/TibiaClientType.hpp"


namespace Amb
{
    namespace Configs
    {
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
                Amb::Client::TibiaClientType clientType;
            } common;

            void toPropertyTreeBuilder(Utils::PropertyTreeBuilder &builder, const std::string &path = "") const
            {
                healer.randBetweenChecks.toPropertyTreeBuilder(builder, path + ".healer.rand_between_checks");
                healer.sleepAfterHotkey.toPropertyTreeBuilder(builder, path + ".healer.sleep_after_hotkey");
                common.captureMode.toPropertyTreeBuilder(builder, path + ".common");
                Amb::Client::toPropertyTreeBuilder(builder, common.clientType, path + ".common");
            }

            static AdvancedSettings fromPtree(boost::property_tree::ptree &tree)
            {
                AdvancedSettings ret;

                ret.healer.randBetweenChecks = FromTo::fromPtree(tree.get_child("healer.rand_between_checks"));
                ret.healer.sleepAfterHotkey = FromTo::fromPtree(tree.get_child("healer.sleep_after_hotkey"));

                ret.common.captureMode = Capture::Mode::fromPtree(tree.get_child("common"));
                ret.common.clientType = Amb::Client::fromPtree(tree.get_child("common"));

                return ret;
            }
        };

        struct Looter
        {
            std::vector<Amb::Ui::Module::Looter::Category> categories;
            std::vector<Amb::Ui::Module::Looter::LootItem> items;

            Amb::Ui::Module::Looter::Category findCategory(const std::string &categoryName) const
            {
                auto pred = [&categoryName](const auto &category)
                {
                    return category.name == categoryName;
                };

                const auto it = std::find_if(std::cbegin(categories),
                                             std::cend(categories),
                                             pred);

                BOOST_ASSERT_MSG(it != std::cend(categories), "Could not find category");

                return *it;
            }

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
                    const auto cat = Amb::Ui::Module::Looter::Category::fromPtree(child.second);
                    healer.categories.emplace_back(cat);
                }

                for (auto &child : tree.get_child("items"))
                {
                    const auto rule = Amb::Ui::Module::Looter::LootItem::fromPtree(child.second);
                    healer.items.emplace_back(rule);
                }

                return healer;
            }
        };

        struct Mlvl
        {
            size_t manaPercentFrom;
            size_t manaPercentTo;
            Utils::Hotkey spellHotkey;
            Utils::Hotkey foodHotkey;

            auto toPtree() const
            {
                Utils::PropertyTreeBuilder builder;
                builder.addElement(Utils::PtreeElement<>{"mana_percent_from", std::to_string(manaPercentFrom)});
                builder.addElement(Utils::PtreeElement<>{"mana_percent_to", std::to_string(manaPercentTo)});
                builder.addElement(Utils::PtreeElement<>{"spell_hotkey", Utils::hotkeyToStdString(spellHotkey)});
                builder.addElement(Utils::PtreeElement<>{"food_hotkey", Utils::hotkeyToStdString(foodHotkey)});

                return builder.buildTree();
            }

            static Mlvl fromPtree(boost::property_tree::ptree &tree)
            {
                Mlvl mlvl;

                mlvl.manaPercentFrom = tree.get_child("mana_percent_from").get_value<size_t>();
                mlvl.manaPercentTo = tree.get_child("mana_percent_to").get_value<size_t>();

                auto strhot = tree.get_child("spell_hotkey").get_value<std::string>();
                mlvl.spellHotkey = Utils::stdStringToHotkey(strhot);

                strhot = tree.get_child("food_hotkey").get_value<std::string>();
                mlvl.foodHotkey = Utils::stdStringToHotkey(strhot);

                return mlvl;
            }
        };

        struct GlobalConfig
        {
            GlobalConfig(const Client::TibiaClientWindowInfo &tibiaClientWindowInfo)
                : tibiaClientWindowInfo{ tibiaClientWindowInfo }
            {}

            DWORD pid{ NULL };
            HWND hwnd{ NULL };
            const Client::TibiaClientWindowInfo &tibiaClientWindowInfo;
            std::string currentConfigFilePath;
            std::string currentCharacterName;

            Config::Module::HealerConfig healerConfig;
            AdvancedSettings advancedSettings;
            Looter looter;
            Mlvl mlvl;

            std::string toString() const
            {
                Utils::PropertyTreeBuilder builder;

                builder.addElement(Utils::PtreeElement<>{"amb.version", AMB_VERSION});
                
                builder.addTree("amb.healer_config", healerConfig.toPtree());
                advancedSettings.toPropertyTreeBuilder(builder, "amb.advanced_settings");
                builder.addTree("amb.looter", looter.toPtree());
                builder.addTree("amb.mlvl", mlvl.toPtree());

                return builder.build();
            }

            static GlobalConfig fromString(const std::string &str, const Client::TibiaClientWindowInfo &info)
            {
                GlobalConfig ret{ info };

                boost::property_tree::ptree tree;
                std::istringstream iss(str);
                boost::property_tree::xml_parser::read_xml(iss, tree);

                ret.healerConfig = Config::Module::HealerConfig::fromPtree(tree.get_child("amb.healer_config"));
                ret.advancedSettings = AdvancedSettings::fromPtree(tree.get_child("amb.advanced_settings"));
                ret.looter = Looter::fromPtree(tree.get_child("amb.looter"));
                ret.mlvl = Mlvl::fromPtree(tree.get_child("amb.mlvl"));

                return ret;
            }
        };
    };
}
