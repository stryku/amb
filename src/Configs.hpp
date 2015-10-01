#pragma once

#include "HealRule.hpp"

#include <vector>
#include <iostream>

namespace AMB
{
    namespace Configs
    {
        /*class Config
        {
        public:
            virtual void serialize( std::ostream &out ) = 0;
            virtual void deserialize( std::istream &in ) = 0;
        };*/

        struct HealerConfig
        {
            std::vector<Modules::Heal::HealRule> rules;
        };

        struct GlobalConfig
        {
            HealerConfig healerConfig;
        };
    };
}