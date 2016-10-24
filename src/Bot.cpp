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
        return [this](Modules::ModuleId module) { toggleModule(module); };
    }

    Bot::TibiaWindowChangedHandler Bot::getTibiaWindowChangedHandler()
    {
        return [this](const std::wstring &str) { tibiaWindowChanged(str); };
    }

    Bot::ResetLayoutHandler Bot::getResetLayoutHandler()
    {
        return [this] { resetLayoutHandler(); };
    }

    void Bot::toggleModule( Modules::ModuleId modId )
    {
        if (!botCore.isModuleRunning(modId))
        {
            configFromUiGenerator.regenerateModule(modId);
            configFromUiGenerator.regenerateAdvancedSettings();
        }

        botCore.toggleModule( modId );
    }

    void Bot::tibiaWindowChanged( const std::wstring &newWindowTitle )
    {
        DWORD pid = Utils::TibiaFinder::findProcessId( newWindowTitle );

        botCore.attachNewProcess( pid );
    }

    void Bot::resetLayoutHandler()
    {
        
    }
}
