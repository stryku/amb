#pragma once

#include "Healer.hpp"
#include "Configs.hpp"

#include "ModulesFactory.hpp"

#include <map>

namespace AMB
{
    namespace Modules
    {
        class ModulesManager
        {
        private:
            std::map<ModuleId, std::shared_ptr<Module>> modules;
            Configs::GlobalConfig &config;

        public:
            ModulesManager( Configs::GlobalConfig &config ) :
                config( config )
            {}

            void run( ModuleId modId )
            {
                switch( modId )
                {
                    case ModuleId::MOD_HEALER: modules[modId] = ModulesFactory::get( modId, config );
                }

                modules[modId]->run();
            }

            void stop( ModuleId modId )
            {
                modules[modId]->stop();
            }
        };
    }
}