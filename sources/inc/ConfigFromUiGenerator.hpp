#pragma once

#include "client/TibiaClientWindowInfo.hpp"

#include <mainwindow.h>

#include <Configs.hpp>
#include <module/ModuleId.hpp>
#include <TibiaFinder.hpp>

namespace Ui {
class MainWindow;
}

namespace Amb
{
    namespace Configs
    {
        class ConfigFromUiGenerator
        {
        public:
            ConfigFromUiGenerator(const MainWindow *mainWindow,
                                  const Client::TibiaClientWindowInfo &tibiaClientWindowInfo,
                                  const Amb::Ui::Module::Healer::HealerRulesTable &healerRulesTable,
                                  const Amb::Ui::Module::Looter::LooterCategoriesTable &looterCategoriesTable,
                                  const Amb::Ui::Module::Looter::LooterItemsTable &looterItemsTable);

            void regenerate();

            const Configs::GlobalConfig& getConfigs() const;

            void regenerateModule(Module::ModuleId moduleId);
            void regenerateAdvancedSettings(); 

            void loadConfigFromString(const std::string &str, const Client::TibiaClientWindowInfo &info);

        private:
            const MainWindow *mainWindow;
            const Amb::Ui::Module::Healer::HealerRulesTable &healerRulesTable;
            const Amb::Ui::Module::Looter::LooterCategoriesTable &looterCategoriesTable;
            const Amb::Ui::Module::Looter::LooterItemsTable &looterItemsTable;
            Amb::Configs::GlobalConfig config;

            void regenerateHealer();
            void regenerateLooter();
            void regeneratePid();
            void regenerateCommon();
            void regenerateAllModules();
        };
    }
}
