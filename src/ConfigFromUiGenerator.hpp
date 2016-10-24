#pragma once

#include <mainwindow.h>

#include <Configs.hpp>
#include <ModuleId.hpp>
#include <TibiaFinder.hpp>

namespace Ui {
class MainWindow;
}

namespace AMB
{
    namespace Configs
    {
        class ConfigFromUiGenerator
        {
        public:
            ConfigFromUiGenerator( const MainWindow *mainWindow,
                                   const HealerRulesTable &healerRulesTable );

            void regenerate();

            const Configs::GlobalConfig& getConfigs() const;

            void regenerateModule( Modules::ModuleId moduleId );
            void regenerateAdvancedSettings();

        private:
            const MainWindow *mainWindow;
            const HealerRulesTable &healerRulesTable;
            AMB::Configs::GlobalConfig config;

            std::wstring getTibiaWindowTitle() const;

            void regenerateHealer();

            void regeneratePid();

            void regenerateCommon();

            void regenerateAllModules();
        };
    }
}
