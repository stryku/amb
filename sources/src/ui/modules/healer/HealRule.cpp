﻿#include "ui/modules/healer/HealRule.hpp"

#include <iostream>

namespace AMB
{
    namespace Modules
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
