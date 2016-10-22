﻿#include "ModulesManager.hpp"

namespace AMB
{
    namespace Modules
    {
        ModulesManager::ModulesManager( const Configs::GlobalConfig &config,
                                        Simulate::Simulator &simulator)
        {
            modules[ModuleId::MOD_HEALER] = std::make_unique<Heal::Healer>( config.healerConfig,
                                                                            simulator );
        }

        void ModulesManager::run( ModuleId modId )
        {
            modules[modId]->run();
        }

        void ModulesManager::stop( ModuleId modId )
        {
            modules[modId]->stop();
        }

        void ModulesManager::toggle( ModuleId modId )
        {
            if( modules[modId]->isRunning() )
                stop( modId );
            else
                run( modId );
        }

        bool ModulesManager::isRunning( ModuleId modId )
        {
            return modules[modId]->isRunning();
        }
    }
}
