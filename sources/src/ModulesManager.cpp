#include "ModulesManager.hpp"

namespace Amb
{
    namespace Module
    {
        ModulesManager::ModulesManager( const Configs::GlobalConfig &config,
                                        Simulate::Simulator &simulator)
        {
            modules[ModuleId::MOD_HEALER] = std::make_unique<Heal::Healer>(config.healerConfig,
                                                                           config.advancedSettings,
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

        void ModulesManager::attachToNewWindow(HWND hwnd)
        {
            for (auto &module : modules)
                module.second->attachToNewWindow(hwnd);
        }
    }
}
