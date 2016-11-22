#include "Bot.hpp"
#include <QMessageBox>

namespace Amb
{
    Bot::Bot(int &argc, char *argv[])
        : application(argc, argv)
        , modulesFactory{ window.getUi() }
        , configFromUiGenerator(&window, window.getHealerRulesTable(), window.getLooterCategoriesTable(), window.getLooterItemsTable())
        , botCore(configFromUiGenerator.getConfigs(), modulesFactory)
        , window{ db }
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
        return [this](Module::ModuleId module) { return toggleModule(module); };
    }

    Bot::TibiaWindowChangedHandler Bot::getTibiaWindowChangedHandler()
    {
        return [this](const std::wstring &str) { tibiaWindowChanged(str); };
    }

    Bot::ConfigProvider Bot::getConfigProvider()
    {
        return [this] {return getConfigurationToSave(); };
    }

    Bot::ConfigLoader Bot::getConfigLoader()
    {
        return[this](const std::string &str) { openConfiguration(str); };
    }


    bool Bot::toggleModule( Module::ModuleId modId )
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
}
