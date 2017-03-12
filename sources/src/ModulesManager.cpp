#include "ModulesManager.hpp"
#include "module/ModulesFactory.hpp"
#include "Simulator.hpp"
#include "config/GlobalConfig.hpp"

namespace Amb
{
    namespace Module
    {
        ModulesManager::ModulesManager(const Config::GlobalConfig &config,
                                       Simulate::Simulator &simulator,
                                       Amb::Module::Factory &modulesFactory,
                                       Monitor::Mouse::MouseMonitorFactory& mousMonitorFactory)
            : modules{ modulesFactory.create(config, simulator, mousMonitorFactory) }
        {/*
            modules[ModuleId::MOD_HEALER] = std::make_unique<Heal::Healer>(config.healerConfig,
                                                                           config.advancedSettings,
                                                                           simulator );*/
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

        void ModulesManager::attachToNewProcess(DWORD pid)
        {
            for (auto &module : modules)
                module.second->attachToNewProcess(pid);
        }

        void ModulesManager::setEnableDebugLogs(bool enabled)
        {
            for (auto &module : modules)
                module.second->setEnableDebugLogs(enabled);
        }
    }
}
