#pragma once
#include "module/ModuleCore.hpp"

#include <memory>

namespace Ui {
    class MainWindow;
}

namespace Amb
{
    namespace Module
    {
        class ModuleCore;
        class ModuleUiRemover;

        class Module
        {
        public:
            virtual ~Module() {}

            void run();
            void hideUi(::Ui::MainWindow *ui);

        private:
            std::unique_ptr<ModuleCore> moduleCore;
            //std::unique_ptr<ModuleUiRemover> moduleUiRemover;
        };
    }
}
