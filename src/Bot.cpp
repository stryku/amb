#include "Bot.hpp"

namespace AMB
{
    Bot::Bot( int &argc, char *argv[] ):
        application( argc, argv ),
        configFromUiGenerator( &window,
                               window.getHealerRulesTable() ),
        botCore( configFromUiGenerator.getConfigs() )
    {
        window.setModuleToggleHandler( getModuleToggleMethod() );
        window.setTtibiaWindowChangedHandler( getTibiaWindowChangedHandler() );
    }

    int Bot::run()
    {
        window.show();
        return application.exec();
    }

    Bot::ModuleToggleMethod Bot::getModuleToggleMethod()
    {
        return std::bind( &Bot::toggleModule,
                          this,
                          std::placeholders::_1 );
    }

    Bot::TibiaWindowChangedHandler Bot::getTibiaWindowChangedHandler()
    {
        return std::bind( &Bot::tibiaWindowChanged,
                          this,
                          std::placeholders::_1 );
    }

    void Bot::toggleModule( Modules::ModuleId modId )
    {
        if( !botCore.isModuleRunning( modId ) )
            configFromUiGenerator.regenerateModule( modId );

        botCore.toggleModule( modId );
    }

    void Bot::tibiaWindowChanged( const std::wstring &newWindowTitle )
    {
        DWORD pid = Utils::TibiaFinder::findProcessId( newWindowTitle );

        botCore.attachNewProcess( pid );
    }

}
