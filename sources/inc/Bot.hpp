﻿#pragma once

#include "BotCore.hpp"
#include "ConfigFromUiGenerator.hpp"
#include "ui/updaters/UiUpdater.hpp"
#include "db/Database.hpp"
#include "module/ModulesFactory.hpp"
#include "ui/updaters/MainWindowTitleUpdater.hpp"
#include "client/TibiaClientWindowRectObserver.hpp"
#include "client/TibiaClientRectCornersObserver.hpp"
#include "log/details/Logger.hpp"

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
        using StringValueObserver = Utils::Observable<std::string>::CallbackType;
        using ClientInfoObserver = std::function<void(const Client::TibiaClientWindowInfo&)>;

        Bot(int &argc, char *argv[]);
        ~Bot() {}

        int run();

        std::string getConfigurationToSave()
        {
            configFromUiGenerator.regenerate();
            return configFromUiGenerator.getConfigs().toString();
        }

        void openConfiguration(const std::string &configuration)
        {
            configFromUiGenerator.loadConfigFromString(configuration,
                                                       tibiaClientWindowInfo);
            uiUpdater.update(configFromUiGenerator.getConfigs(), window.getControls());
        }

    private:
        bool toggleModule(Module::ModuleId modId);
        void tibiaWindowChanged(const std::wstring &newWindowTitle);

        ModuleToggleMethod getModuleToggleMethod();
        TibiaWindowChangedHandler getTibiaWindowChangedHandler();
        ConfigProvider getConfigProvider();
        //CurrentConfigFilePathProvider getCurrentConfigFilePathProvider();
        ConfigLoader getConfigLoader();
        StringValueObserver getCharacterNameObserver();
        StringValueObserver getScriptNameObserver();
        ClientInfoObserver getClientRectObserver();

        QApplication application;
        MainWindow window;
        Amb::Module::Factory modulesFactory;
        Amb::Configs::ConfigFromUiGenerator configFromUiGenerator;
        Ui::Updaters::MainWindowTitleUpdater mainWindowTitleUpdater;
        Amb::Ui::Updaters::UiUpdater uiUpdater;
        Utils::Observable<std::string> currentConfigFilePath;
        Utils::Observable<std::string> currentCharacterName;
        //RectCorners currentTibiaClientWindowRectCorners;
        //Rect currentTibiaClientWindowRect;
        Client::TibiaClientWindowInfo tibiaClientWindowInfo;
        Client::TibiaClientWindowRectObserver clientRectObserver;
        Amb::BotCore botCore;
        const Amb::Db::Database db;
    };

}
