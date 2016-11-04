#pragma once

#include "mainwindow.h"
#include <QApplication>

#include <BotCore.hpp>
#include <ConfigFromUiGenerator.hpp>


namespace AMB
{
class Bot
{
public:
    using ModuleToggleMethod = std::function<bool(Modules::ModuleId)>;
    using TibiaWindowChangedHandler = std::function<void(const std::wstring&)>;
    using ResetLayoutHandler = std::function<void()>;
    using ConfigProvider = std::function<std::string()>;

    Bot( int &argc, char *argv[] );
    ~Bot() {}

    int run();

    std::string getConfigurationToSave()
    {
        configFromUiGenerator.regenerate();
        return configFromUiGenerator.getConfigs().toString();
    }

    void openConfiguration()
    {

    }

private:
    bool toggleModule( Modules::ModuleId modId );
    void tibiaWindowChanged( const std::wstring &newWindowTitle );
    void resetLayoutHandler();

    ModuleToggleMethod getModuleToggleMethod();
    TibiaWindowChangedHandler getTibiaWindowChangedHandler();
    ResetLayoutHandler getResetLayoutHandler();
    ConfigProvider getConfigProvider();

    QApplication application;
    MainWindow window;
    AMB::Configs::ConfigFromUiGenerator configFromUiGenerator;
    AMB::BotCore botCore;
};

}
