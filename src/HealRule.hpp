#pragma once

#include "utils.hpp"

namespace AMB
{
    namespace Modules
    {
        namespace Heal
        {
            class HealRule
            {
                size_t minHeal, maxHeal, minMana, maxMana;
                Utils::Hotkey hotkey;
            };
        }
    }
}