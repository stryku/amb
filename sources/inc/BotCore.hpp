#pragma once

#include "Simulator.hpp"
#include "ModulesManager.hpp"
#include "ModuleId.hpp"

#include <vector>
#include <functional>

namespace Amb
{
    class BotCore
    {
    private:
        DWORD attachedProcess{ NULL };
        Simulate::Simulator simulator;
        Module::ModulesManager modulesManager;

    public:
        BotCore( const Configs::GlobalConfig &config );

        void startModule( Module::ModuleId moduleId );
        void attachNewProcess( DWORD pid );
        void toggleModule( Amb::Module::ModuleId modId );
        bool isModuleRunning( Module::ModuleId modId );
        DWORD getAttachedProcess() const { return attachedProcess; }
    };
}
