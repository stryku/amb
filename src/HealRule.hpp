#pragma once

#include "utils/PropertyTreeBuilder.hpp"
#include "utils.hpp"

namespace AMB
{
    namespace Modules
    {
        namespace Heal
        {
            struct HealRule
            {
                size_t minHp, maxHp, minMana, maxMana;
                Utils::Hotkey hotkey;

                bool passed( size_t characterHp, size_t characterMana ) const;
                void toPropertyTreeBuilder(Utils::PropertyTreeBuilder &builder, const std::string &path = "") const
                {
                    const auto elements = 
                    {
                        Utils::PtreeElement<>{ path + ".hp.min", utils::toString(minHp) },
                        Utils::PtreeElement<>{ path + ".hp.max", utils::toString(maxHp) },
                        Utils::PtreeElement<>{ path + ".mana.min", utils::toString(minMana) },
                        Utils::PtreeElement<>{ path + ".mana.max", utils::toString(maxMana) },
                        Utils::PtreeElement<>{ path + ".hotkey", Utils::hotkeyToStdString(hotkey) }
                    };

                    builder.addElements(elements);
                }

                static HealRule fromPtree(boost::property_tree::ptree &tree)
                {
                    HealRule rule;

                    rule.minHp = tree.get_child("hp.min").get_value<size_t>();
                    rule.maxHp = tree.get_child("hp.max").get_value<size_t>();
                    rule.minMana = tree.get_child("mana.min").get_value<size_t>();
                    rule.maxMana = tree.get_child("mana.max").get_value<size_t>();

                    auto strhot = tree.get_child("hotkey").get_value<std::string>();
                    rule.hotkey = Utils::stdStringToHotkey(strhot);

                    return rule;
                }
            };
        }
    }
}
