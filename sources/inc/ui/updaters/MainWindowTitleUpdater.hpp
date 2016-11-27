#pragma once

#include "ui/updaters/details/MainWindowTitleBuilder.hpp"

#include <string>

class MainWindow;

namespace Amb
{
    namespace Ui
    {
        namespace Updaters
        {
            class MainWindowTitleUpdater
            {
            public:
                MainWindowTitleUpdater(MainWindow &mainWindow);

                void setBasic();
                void characterNameChanged(const std::string &name);
                void scriptNameChanged(const std::string &scriptName);

            private:
                void setTitle(const std::string &title);

                MainWindow &mainWindow;
                details::MainWindowTitleBuilder titleBuilder;
            };
        }
    }
}
