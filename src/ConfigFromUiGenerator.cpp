#include "ConfigFromUiGenerator.hpp"
#include <mainwindow.h>

namespace AMB
{
namespace Configs
{
    ConfigFromUiGenerator::ConfigFromUiGenerator( const MainWindow *mainWindow,
                                                  const HealerRulesTable &healerRulesTable ) :
        mainWindow( mainWindow ),
        healerRulesTable( healerRulesTable )
    {}

    void ConfigFromUiGenerator::regenerate()
    {
        regenerateCommon();
        regenerateAllModules();
    }

    const Configs::GlobalConfig& ConfigFromUiGenerator::getConfigs() const
    {
        return config;
    }

    void ConfigFromUiGenerator::regenerateModule( Modules::ModuleId moduleId )
    {
        switch( moduleId )
        {
            case Modules::ModuleId::MOD_HEALER: regenerateHealer();
        }
    }



    void ConfigFromUiGenerator::regenerateHealer()
    {
        std::cout<<"regenerating healer config\n";
        config.healerConfig.rules = healerRulesTable.getRules();
    }

    void ConfigFromUiGenerator::regeneratePid()
    {
        auto title = mainWindow->getTibiaWindowTitle();

        config.pid = Utils::TibiaFinder::findProcessId( title );
    }

    void ConfigFromUiGenerator::regenerateCommon()
    {
        regeneratePid();
    }

    void ConfigFromUiGenerator::regenerateAllModules()
    {
        regenerateModule( Modules::ModuleId::MOD_HEALER );
    }
}
}
