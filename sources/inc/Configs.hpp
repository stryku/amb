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
#include "config/module/MlvlConfig.hpp"



#include <boost/assert.hpp>

#include <vector>
#include <iostream>
#include "client/TibiaClientType.hpp"


namespace Amb
{
    namespace Configs
    {
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
            Config::Module::MlvlConfig mlvl;

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
                ret.mlvl = Config::Module::MlvlConfig::fromPtree(tree.get_child("amb.mlvl"));

                return ret;
            }
        };
    };
}
