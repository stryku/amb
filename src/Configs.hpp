#pragma once

#include "utils.hpp"
#include "HealRule.hpp"
#include "utils/Structs.hpp"

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

        struct AdvancedSettings
        {
            struct
            {
                FromTo randBetweenChecks;
                FromTo sleepAfterHotkey;
            } healer;
        };

        struct GlobalConfig
        {
            DWORD pid;
            HWND hwnd;
            HealerConfig healerConfig;
            AdvancedSettings advancedSettings;
        };
    };
}
