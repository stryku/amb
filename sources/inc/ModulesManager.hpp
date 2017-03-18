#pragma once

//#include "Configs.hpp"
#include "module/ModuleId.hpp"
#include "module/ModuleCore.hpp"

#include <unordered_map>

namespace Amb
{
    namespace Monitor
    {
        namespace Mouse
        {
            class MouseMonitorFactory;
        }
    }

    namespace Config
    {
        struct GlobalConfig;
    }

    namespace Simulate
    {
        class Simulator;
    }

    namespace Module
    {
        class Factory;

        class ModulesManager
        {
        private:
            std::unordered_map<ModuleId, std::unique_ptr<ModuleCore>> modules;

        public:
            ModulesManager(const Config::GlobalConfig &config,
                           Simulate::Simulator &simulator,
                           Amb::Module::Factory &modulesFactory,
                           Monitor::Mouse::MouseMonitorFactory& mousMonitorFactory);

            void run( ModuleId modId );
            void stop( ModuleId modId );
            void toggle( ModuleId modId );
            bool isRunning( ModuleId modId );

            void attachToNewWindow(HWND hwnd);
            void attachToNewProcess(DWORD pid);

            void setEnableDebugLogs(bool enabled);
        };
    }
}
