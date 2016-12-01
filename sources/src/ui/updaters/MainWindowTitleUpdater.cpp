#include "ui/updaters/MainWindowTitleUpdater.hpp"

#include "mainwindow.h"

namespace Amb
{
    namespace Ui
    {
        namespace Updaters
        {
            MainWindowTitleUpdater::MainWindowTitleUpdater(MainWindow &mainWindow)
                : mainWindow{ mainWindow }
            {}

            void MainWindowTitleUpdater::setBasic()
            {
                const auto newTitle = titleBuilder.withCharacterName("")
                                                  .withScriptName("")
                                                  .build();

                setTitle(newTitle);
            }

            void MainWindowTitleUpdater::characterNameChanged(const std::string &name)
            {
                const auto newTitle = titleBuilder.withCharacterName(name).build();
                setTitle(newTitle);
            }

            void MainWindowTitleUpdater::scriptNameChanged(const std::string &scriptName)
            {
                const auto newTitle = titleBuilder.withScriptName(scriptName).build();
                setTitle(newTitle);
            }

            void MainWindowTitleUpdater::setTitle(const std::string &title)
            {
                mainWindow.setWindowTitle(QString::fromStdString(title));
            }
        }
    }
}
