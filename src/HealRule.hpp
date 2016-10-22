﻿#pragma once

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
            };
        }
    }
}
