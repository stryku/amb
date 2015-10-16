#pragma once

#include "Healer.hpp"
#include "Configs.hpp"
#include "ModuleId.hpp"

#include <map>

namespace AMB
{
    namespace Modules
    {
        class ModulesManager
        {
        private:
            std::map<ModuleId, std::unique_ptr<Module>> modules;
            Configs::GlobalConfig &config;

        public:
            ModulesManager( Configs::GlobalConfig &config ) : // todo change to pointer to ui from qt
                config( config )
            {
                modules[ModuleId::MOD_HEALER] = std::make_unique<Heal::Healer>( config );
            }

            void run( ModuleId modId )
            {
                modules[modId]->run();
            }

            void stop( ModuleId modId )
            {
                modules[modId]->stop();
            }
        };
    }
}