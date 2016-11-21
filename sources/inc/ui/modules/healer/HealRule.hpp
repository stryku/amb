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

                HealRule() = default;
                HealRule(size_t minHp,
                         size_t &maxHp,
                         size_t &minMana,
                         size_t &maxMana,
                         Utils::Hotkey hotkey)
                    : minHp{ minHp }
                    , maxHp{ maxHp }
                    , minMana{ minMana }
                    , maxMana{ maxMana }
                    , hotkey{ hotkey }
                {}

                HealRule(const std::string &minHp,
                         const std::string &maxHp,
                         const std::string &minMana,
                         const std::string &maxMana,
                         const std::string &hotkey)
                    : minHp{ std::stoul(minHp) }
                    , maxHp{ std::stoul(maxHp) }
                    , minMana{ std::stoul(minMana) }
                    , maxMana{ std::stoul(maxMana) }
                    , hotkey{ Utils::stdStringToHotkey(hotkey) }
                {}

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

                auto toPtree() const
                {
                    Utils::PropertyTreeBuilder builder;

                    const auto elements =
                    {
                        Utils::PtreeElement<>{ "hp.min", utils::toString(minHp) },
                        Utils::PtreeElement<>{ "hp.max", utils::toString(maxHp) },
                        Utils::PtreeElement<>{ "mana.min", utils::toString(minMana) },
                        Utils::PtreeElement<>{ "mana.max", utils::toString(maxMana) },
                        Utils::PtreeElement<>{ "hotkey", Utils::hotkeyToStdString(hotkey) }
                    };

                    return builder.addElements(elements).buildTree();
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
