#include "ConfigFromUiGenerator.hpp"
#include <mainwindow.h>

namespace AMB
{
    namespace Configs
    {
        ConfigFromUiGenerator::ConfigFromUiGenerator(const MainWindow *mainWindow,
                                                     const AMB::Ui::Modules::Healer::HealerRulesTable &healerRulesTable,
                                                     const AMB::Ui::Modules::Looter::LooterCategoriesTable &looterCategoriesTable,
                                                     const AMB::Ui::Modules::Looter::LooterItemsTable &looterItemsTable)
            : mainWindow{ mainWindow }
            , healerRulesTable{ healerRulesTable }
            , looterCategoriesTable{ looterCategoriesTable }
            , looterItemsTable{ looterItemsTable }
        {}

        void ConfigFromUiGenerator::regenerate()
        {
            regenerateCommon();
            regenerateAllModules();
            regenerateAdvancedSettings();
        }

        const Configs::GlobalConfig& ConfigFromUiGenerator::getConfigs() const
        {
            return config;
        }

        void ConfigFromUiGenerator::regenerateModule(Modules::ModuleId moduleId)
        {
            switch (moduleId)
            {
                case Modules::ModuleId::MOD_HEALER: regenerateHealer();
                case Modules::ModuleId::MOD_LOOTER: regenerateLooter();
            }
        }



        void ConfigFromUiGenerator::regenerateHealer()
        {
            qDebug("regenerating healer config");
            config.healerConfig.rules = healerRulesTable.getRules();
        }
        
        void ConfigFromUiGenerator::regenerateLooter()
        {
            qDebug("regenerating looter config");
            config.looter.categories = looterCategoriesTable.getCategories();
            config.looter.items = looterItemsTable.getItems();
        }

        void ConfigFromUiGenerator::regenerateAdvancedSettings()
        {
            qDebug("ConfigFromUiGenerator::regenerateAdvancedSettings");
            const auto healerSettingsControls = mainWindow->getAdvancedSettingsHealer();
            config.advancedSettings.healer = {
                Utils::getFromToFromEdits(healerSettingsControls.betweenChecks),
                Utils::getFromToFromEdits(healerSettingsControls.sleepAfterHotkey)
            };
        }


        void ConfigFromUiGenerator::regeneratePid()
        {
            auto title = mainWindow->getTibiaWindowTitle();

            config.pid = Utils::TibiaFinder::findProcessId(title);
        }

        void ConfigFromUiGenerator::regenerateCommon()
        {
            regeneratePid();
        }

        void ConfigFromUiGenerator::regenerateAllModules()
        {
            regenerateModule(Modules::ModuleId::MOD_HEALER);
        }

        void ConfigFromUiGenerator::loadConfigFromString(const std::string &str)
        {
            auto newConfig = AMB::Configs::GlobalConfig::fromString(str);
            config.healerConfig = newConfig.healerConfig;
            config.advancedSettings = newConfig.advancedSettings;
        }
    }
}
