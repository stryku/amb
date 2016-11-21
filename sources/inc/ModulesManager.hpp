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
            std::map<ModuleId, std::unique_ptr<ModuleCore>> modules;

        public:
            ModulesManager( const Configs::GlobalConfig &config,
                            Simulate::Simulator &simulator);

            void run( ModuleId modId );
            void stop( ModuleId modId );
            void toggle( ModuleId modId );
            bool isRunning( ModuleId modId );

            void attachToNewWindow(HWND hwnd);
        };
    }
}
