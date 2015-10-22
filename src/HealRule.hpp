#pragma once

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

                HealRule() {}
                HealRule( size_t minHp,
                          size_t maxHp,
                          size_t minMana,
                          size_t maxMana,
                          size_t size_tHotkey ) :
                    minHp( minHp ),
                    maxHp( maxHp ),
                    minMana( minMana ),
                    maxMana( maxMana )
                {
                    hotkey = Utils::size_tToHotkey( size_tHotkey );
                }

                bool passed( size_t characterHp, size_t characterMana ) const
                {
                    return minHp <= characterHp && characterHp <= maxHp
                        && minMana <= characterMana && characterMana <= maxMana;
                }
            };
        }
    }
}
