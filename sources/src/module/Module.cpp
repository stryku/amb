#include "module/Module.hpp"
#include "module/ModuleCore.hpp"

#include "ui_mainwindow.h"

namespace Amb
{
    namespace Module
    {
        void Module::run()
        {
            moduleCore->run();
        }

        void Module::hideUi(::Ui::MainWindow *ui)
        {

        }
    }
}