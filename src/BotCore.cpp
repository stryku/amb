﻿#include "BotCore.hpp"

namespace AMB
{
    BotCore::BotCore( const Configs::GlobalConfig &config ) :
        modulesManager( config,
                        simulator )
    {}

    void BotCore::startModule( Modules::ModuleId moduleId )
    {
        modulesManager.run( moduleId );
    }

    void BotCore::attachNewProcess( DWORD pid )
    {
        auto hwnd = Utils::TibiaFinder::pidToHwnd(pid);
        simulator.attachToNewWindow(hwnd);
        modulesManager.attachToNewWindow(hwnd);
        attachedProcess = pid;
    }

    void BotCore::toggleModule( AMB::Modules::ModuleId modId )
    {
        modulesManager.toggle( modId );
    }

    bool BotCore::isModuleRunning( Modules::ModuleId modId )
    {
        return modulesManager.isRunning( modId );
    }
}
