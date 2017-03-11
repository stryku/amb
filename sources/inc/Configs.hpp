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
#include "config/module/AdvancedSettingsConfig.hpp"
#include "config/module/LooterConfig.hpp"



#include <boost/assert.hpp>

#include <vector>
#include <iostream>
#include "client/TibiaClientType.hpp"


namespace Amb
{
    namespace Configs
    {
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
            Config::Module::AdvancedSettingsConfig advancedSettings;
            Config::Module::LooterConfig looter;
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
                ret.advancedSettings = Config::Module::AdvancedSettingsConfig::fromPtree(tree.get_child("amb.advanced_settings"));
                ret.looter = Config::Module::LooterConfig::fromPtree(tree.get_child("amb.looter"));
                ret.mlvl = Mlvl::fromPtree(tree.get_child("amb.mlvl"));

                return ret;
            }
        };
    };
}
