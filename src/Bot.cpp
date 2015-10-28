#include "Bot.hpp"

namespace AMB
{
    Bot::Bot( int &argc, char *argv[] ):
        application( argc, argv ),
        configFromUiGenerator( &window,
                               window.getHealerRulesTable() ),
        botCore( configFromUiGenerator.getConfigs() )
    {
        window.setModuleToggleHandler( botCore.getModuleToggleHandler() );
    }

    int Bot::run()
    {
        window.show();
        return application.exec();
    }

}
