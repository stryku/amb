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
            };
        }
    }
}
