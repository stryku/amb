#include "Bot.hpp"
#include <QMessageBox>

namespace AMB
{
    Bot::Bot(int &argc, char *argv[]) :
        application(argc, argv),
        configFromUiGenerator(&window,
                              window.getHealerRulesTable()),
        botCore(configFromUiGenerator.getConfigs())
    {
        window.setModuleToggleHandler(getModuleToggleMethod());
        window.setTtibiaWindowChangedHandler(getTibiaWindowChangedHandler());
        window.setConfigProvider(getConfigProvider());
        window.setConfigLoader(getConfigLoader());
    }

    int Bot::run()
    {
        window.show();
        return application.exec();
    }

    Bot::ModuleToggleMethod Bot::getModuleToggleMethod()
    {
        return [this](Modules::ModuleId module) { return toggleModule(module); };
    }

    Bot::TibiaWindowChangedHandler Bot::getTibiaWindowChangedHandler()
    {
        return [this](const std::wstring &str) { tibiaWindowChanged(str); };
    }

    Bot::ResetLayoutHandler Bot::getResetLayoutHandler()
    {
        return [this] { resetLayoutHandler(); };
    }

    Bot::ConfigProvider Bot::getConfigProvider()
    {
        return [this] {return getConfigurationToSave(); };
    }

    Bot::ConfigLoader Bot::getConfigLoader()
    {
        return[this](const std::string &str) { openConfiguration(str); };
    }


    bool Bot::toggleModule( Modules::ModuleId modId )
    {
        if (botCore.getAttachedProcess() == NULL)
        {
            QMessageBox msgBox;
            msgBox.setText("Error");
            msgBox.setInformativeText("You need to select Tibia window first.");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
            return false;
        }

        if (!botCore.isModuleRunning(modId))
        {
            configFromUiGenerator.regenerateModule(modId);
            configFromUiGenerator.regenerateAdvancedSettings();
        }

        botCore.toggleModule( modId );
        return true;
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
