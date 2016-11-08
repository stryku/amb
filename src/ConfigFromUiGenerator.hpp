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
                                   const AMB::Ui::Modules::Healer::HealerRulesTable &healerRulesTable );

            void regenerate();

            const Configs::GlobalConfig& getConfigs() const;

            void regenerateModule( Modules::ModuleId moduleId );
            void regenerateAdvancedSettings();

            void loadConfigFromString(const std::string &str);

        private:
            const MainWindow *mainWindow;
            const AMB::Ui::Modules::Healer::HealerRulesTable &healerRulesTable;
            AMB::Configs::GlobalConfig config;

            void regenerateHealer();
            void regeneratePid();
            void regenerateCommon();
            void regenerateAllModules();
        };
    }
}
