#pragma once

#include "utils.hpp"
#include "HealRule.hpp"

#include <vector>
#include <iostream>

namespace AMB
{
    namespace Configs
    {
        struct HealerConfig
        {
            std::vector<Modules::Heal::HealRule> rules;
        };

        struct GlobalConfig
        {
            DWORD pid;
            HealerConfig healerConfig;
        };
    };
}
