#pragma once

#include "Simulator.hpp"
#include "TibiaStuffReader.hpp"
#include "ModulesManager.hpp"
#include "ModuleId.hpp"

#include <vector>

namespace AMB
{
    class Bot
    {
    private:
        Simulate::Simulator simulator;
        Memory::TibiaStuffReader reader;
        Modules::ModulesManager modulesManager;

    public:
        Bot( Configs::GlobalConfig &config ) :
            modulesManager( config )
        {}

        void startModule( Modules::ModuleId moduleId )
        {
            modulesManager.run( moduleId );
        }

        void attachNewProcess( DWORD pid )
        {
            simulator.attachNewProcess( pid );
            reader.attachNewProcess( pid );
        }
    };
}