#pragma once

#include "Configs.hpp"
#include "Module.hpp"
#include "Healer.hpp"

#include <memory>

namespace AMB
{
    namespace Modules
    {
        enum class ModuleId
        {
            MOD_HEALER = 0
        };

        class ModulesFactory
        {
        public:
            static std::shared_ptr<Module> get( ModuleId modId, Configs::GlobalConfig &config )
            {
                switch( modId )
                {
                    case ModuleId::MOD_HEALER: return std::make_shared<Heal::Healer>( config );
                }
            }
        };
    }
}