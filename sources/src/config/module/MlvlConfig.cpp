#include "config/module/MlvlConfig.hpp"

#include "utils/PropertyTreeBuilder.hpp"

namespace Amb
{
    namespace Config
    {
        namespace Module
        {
            boost::property_tree::ptree MlvlConfig::toPtree() const
            {
                Utils::PropertyTreeBuilder builder;
                builder.addElement(Utils::PtreeElement<>{"mana_percent_from", std::to_string(manaPercentFrom)});
                builder.addElement(Utils::PtreeElement<>{"mana_percent_to", std::to_string(manaPercentTo)});
                builder.addElement(Utils::PtreeElement<>{"spell_hotkey", Utils::hotkeyToStdString(spellHotkey)});
                builder.addElement(Utils::PtreeElement<>{"food_hotkey", Utils::hotkeyToStdString(foodHotkey)});

                return builder.buildTree();
            }

            MlvlConfig MlvlConfig::fromPtree(boost::property_tree::ptree &tree)
            {
                MlvlConfig mlvl;

                mlvl.manaPercentFrom = tree.get_child("mana_percent_from").get_value<size_t>();
                mlvl.manaPercentTo = tree.get_child("mana_percent_to").get_value<size_t>();

                auto strhot = tree.get_child("spell_hotkey").get_value<std::string>();
                mlvl.spellHotkey = Utils::stdStringToHotkey(strhot);

                strhot = tree.get_child("food_hotkey").get_value<std::string>();
                mlvl.foodHotkey = Utils::stdStringToHotkey(strhot);

                return mlvl;
            }
        }
    }
}
