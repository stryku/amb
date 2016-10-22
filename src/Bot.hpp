#pragma once

#include "mainwindow.hpp"
#include <QApplication>

#include <BotCore.hpp>
#include <ConfigFromUiGenerator.hpp>


namespace AMB
{
class Bot
{
public:
    typedef std::function<void( Modules::ModuleId )> ModuleToggleMethod;
    typedef std::function<void( const std::wstring& )> TibiaWindowChangedHandler;

    Bot( int &argc, char *argv[] );
    ~Bot() {}


    int run();

private:
    void toggleModule( Modules::ModuleId modId );
    void tibiaWindowChanged( const std::wstring &newWindowTitle );

    ModuleToggleMethod getModuleToggleMethod();
    TibiaWindowChangedHandler getTibiaWindowChangedHandler();

    QApplication application;
    MainWindow window;
    AMB::Configs::ConfigFromUiGenerator configFromUiGenerator;
    AMB::BotCore botCore;
};

}
