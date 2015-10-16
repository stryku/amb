#pragma once

#include "HealRule.hpp"

#include <vector>
#include <iostream>

namespace AMB
{
    namespace Configs
    {
        struct Config
        {
            virtual void fromUi() = 0; // todo add ui ptr
        };

        struct HealerConfig : public Config
        {
            std::vector<Modules::Heal::HealRule> rules;

            void fromUi()
            {

            }
        };

        struct GlobalConfig
        {
            DWORD pid;
            HealerConfig healerConfig;
        };
    };
}