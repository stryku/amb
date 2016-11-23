#pragma once

#include "BotCore.hpp"
#include "ConfigFromUiGenerator.hpp"
#include "ui/updaters/UiUpdater.hpp"
#include "db/Database.hpp"
#include "module/ModulesFactory.hpp"

#include "mainwindow.h"

#include <QApplication>


namespace Amb
{
class Bot
{
public:
    using ModuleToggleMethod = std::function<bool(Module::ModuleId)>;
    using TibiaWindowChangedHandler = std::function<void(const std::wstring&)>;
    using ResetLayoutHandler = std::function<void()>;
    using ConfigProvider = std::function<std::string()>;
    using CurrentConfigFilePathProvider = std::function<std::string()>;
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
    bool toggleModule( Module::ModuleId modId );
    void tibiaWindowChanged( const std::wstring &newWindowTitle );

    ModuleToggleMethod getModuleToggleMethod();
    TibiaWindowChangedHandler getTibiaWindowChangedHandler();
    ConfigProvider getConfigProvider();
    CurrentConfigFilePathProvider getCurrentConfigFilePathProvider();
    ConfigLoader getConfigLoader();

    QApplication application;
    MainWindow window;
    Amb::Module::Factory modulesFactory;
    Amb::Configs::ConfigFromUiGenerator configFromUiGenerator;
    Amb::Ui::Updaters::UiUpdater uiUpdater;
    Amb::BotCore botCore;
    const Amb::Db::Database db;
};

}
