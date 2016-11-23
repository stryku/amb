#include "ui/modules/healer/HealRule.hpp"

#include <iostream>

namespace Amb
{
    namespace Module
    {
        namespace Heal
        {
            bool HealRule::passed( size_t characterHp, size_t characterMana ) const
            {
                return minHp <= characterHp && characterHp <= maxHp
                    && minMana <= characterMana && characterMana <= maxMana;
            }
        }
    }
}
