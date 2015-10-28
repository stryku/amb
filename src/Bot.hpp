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
    Bot( int &argc, char *argv[] );
    ~Bot() {}


    int run();

private:
    QApplication application;
    MainWindow window;
    AMB::Configs::ConfigFromUiGenerator configFromUiGenerator;
    AMB::BotCore botCore;
};

}
