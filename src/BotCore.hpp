#pragma once

#include "Simulator.hpp"
#include "TibiaStuffReader.hpp"
#include "ModulesManager.hpp"
#include "ModuleId.hpp"

#include <vector>
#include <functional>

namespace AMB
{
    class BotCore
    {
    private:
        typedef std::function<void( Modules::ModuleId )> ModuleToggleHandler;

        Memory::TibiaStuffReader reader;
        Simulate::Simulator simulator;
        Modules::ModulesManager modulesManager;

    public:
        BotCore( const Configs::GlobalConfig &config );

        void startModule( Modules::ModuleId moduleId );

        void attachNewProcess( DWORD pid );

        void moduleToggleHandler( AMB::Modules::ModuleId modId );

        ModuleToggleHandler getModuleToggleHandler();
    };
}
