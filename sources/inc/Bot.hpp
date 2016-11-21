#pragma once

#include "BotCore.hpp"
#include "ConfigFromUiGenerator.hpp"
#include "ui/updaters/UiUpdater.hpp"
#include "db/Database.hpp"

#include "mainwindow.h"

#include <QApplication>


namespace AMB
{
class Bot
{
public:
    using ModuleToggleMethod = std::function<bool(Modules::ModuleId)>;
    using TibiaWindowChangedHandler = std::function<void(const std::wstring&)>;
    using ResetLayoutHandler = std::function<void()>;
    using ConfigProvider = std::function<std::string()>;
    using ConfigLoader = std::function<void(const std::string&)>;

    Bot( int &argc, char *argv[] );
    ~Bot() {}

    int run();

    std::string getConfigurationToSave()
    {
        configFromUiGenerator.regenerate();
        return configFromUiGenerator.getConfigs().toString();
    }

    void openConfiguration(const std::string &configuration)
    {
        configFromUiGenerator.loadConfigFromString(configuration);
        uiUpdater.update(configFromUiGenerator.getConfigs(), window.getControls());
    }

private:
    bool toggleModule( Modules::ModuleId modId );
    void tibiaWindowChanged( const std::wstring &newWindowTitle );

    ModuleToggleMethod getModuleToggleMethod();
    TibiaWindowChangedHandler getTibiaWindowChangedHandler();
    ConfigProvider getConfigProvider();
    ConfigLoader getConfigLoader();

    QApplication application;
    MainWindow window;
    AMB::Configs::ConfigFromUiGenerator configFromUiGenerator;
    AMB::Ui::Updaters::UiUpdater uiUpdater;
    AMB::BotCore botCore;
    const AMB::Db::Database db;
};

}
