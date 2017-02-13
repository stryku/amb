#pragma once

#include "Simulator.hpp"
#include "ModulesManager.hpp"
#include "module/ModuleId.hpp"

#include <vector>
#include <functional>

namespace Amb
{
    namespace Module
    {
        class Factory;
    }

    class BotCore
    {
    private:
        using EnableDebugLogsObserver = Utils::Observable<bool>::CallbackType;

        DWORD attachedProcess{ NULL };
        Simulate::Simulator simulator;
        Module::ModulesManager modulesManager;

    public:
        BotCore(const Configs::GlobalConfig &config,
                Amb::Module::Factory &modulesFactory);

        void startModule( Module::ModuleId moduleId );
        void attachNewProcess( DWORD pid );
        void toggleModule( Amb::Module::ModuleId modId );
        bool isModuleRunning( Module::ModuleId modId );
        DWORD getAttachedProcess() const { return attachedProcess; }
        EnableDebugLogsObserver getEnableDebugLogsObserver();
    };
}
