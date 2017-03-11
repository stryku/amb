#include "config/GlobalConfig.hpp"

#include <boost/assert.hpp>

#include <vector>

namespace Amb
{
    namespace Config
    {
        GlobalConfig::GlobalConfig(const Client::TibiaClientWindowInfo &tibiaClientWindowInfo)
            : tibiaClientWindowInfo{ tibiaClientWindowInfo }
        {}

        std::string GlobalConfig::toString() const
        {
            Utils::PropertyTreeBuilder builder;

            builder.addElement(Utils::PtreeElement<>{"amb.version", AMB_VERSION});

            builder.addTree("amb.healer_config", healerConfig.toPtree());
            advancedSettings.toPropertyTreeBuilder(builder, "amb.advanced_settings");
            builder.addTree("amb.looter", looter.toPtree());
            builder.addTree("amb.mlvl", mlvl.toPtree());

            return builder.build();
        }

        GlobalConfig GlobalConfig::fromString(const std::string &str, 
                                              const Client::TibiaClientWindowInfo &info)
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
    }
}
