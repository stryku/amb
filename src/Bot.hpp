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
    using ModuleToggleMethod = std::function<void(Modules::ModuleId)>;
    using TibiaWindowChangedHandler = std::function<void(const std::wstring&)>;
    using ResetLayoutHandler = std::function<void()>;

    Bot( int &argc, char *argv[] );
    ~Bot() {}


    int run();

private:
    void toggleModule( Modules::ModuleId modId );
    void tibiaWindowChanged( const std::wstring &newWindowTitle );
    void resetLayoutHandler();

    ModuleToggleMethod getModuleToggleMethod();
    TibiaWindowChangedHandler getTibiaWindowChangedHandler();
    ResetLayoutHandler getResetLayoutHandler();

    QApplication application;
    MainWindow window;
    AMB::Configs::ConfigFromUiGenerator configFromUiGenerator;
    AMB::BotCore botCore;
};

}
