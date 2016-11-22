#pragma once

#include "Configs.hpp"
#include "module/ModuleId.hpp"
#include "module/ModuleCore.hpp"

#include <unordered_map>

namespace Amb
{
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
            ModulesManager(const Configs::GlobalConfig &config,
                           Simulate::Simulator &simulator,
                           Amb::Module::Factory &modulesFactory);

            void run( ModuleId modId );
            void stop( ModuleId modId );
            void toggle( ModuleId modId );
            bool isRunning( ModuleId modId );

            void attachToNewWindow(HWND hwnd);
        };
    }
}
