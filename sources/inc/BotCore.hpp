#pragma once

#include "Simulator.hpp"
#include "ModulesManager.hpp"
#include "ModuleId.hpp"

#include <vector>
#include <functional>

namespace AMB
{
    class BotCore
    {
    private:
        DWORD attachedProcess{ NULL };
        Simulate::Simulator simulator;
        Modules::ModulesManager modulesManager;

    public:
        BotCore( const Configs::GlobalConfig &config );

        void startModule( Modules::ModuleId moduleId );
        void attachNewProcess( DWORD pid );
        void toggleModule( AMB::Modules::ModuleId modId );
        bool isModuleRunning( Modules::ModuleId modId );
        DWORD getAttachedProcess() const { return attachedProcess; }
    };
}
