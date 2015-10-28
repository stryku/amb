#include "BotCore.hpp"

namespace AMB
{
    BotCore::BotCore( const Configs::GlobalConfig &config ) :
        modulesManager( config,
                        reader,
                        simulator )
    {}

    void BotCore::startModule( Modules::ModuleId moduleId )
    {
        modulesManager.run( moduleId );
    }

    void BotCore::attachNewProcess( DWORD pid )
    {
        simulator.attachNewProcess( pid );
        reader.attachNewProcess( pid );
    }

    void BotCore::moduleToggleHandler( AMB::Modules::ModuleId modId )
    {}

    BotCore::ModuleToggleHandler BotCore::getModuleToggleHandler()
    {
        return std::bind( &BotCore::moduleToggleHandler,
                          this,
                          std::placeholders::_1 );
    }
}
