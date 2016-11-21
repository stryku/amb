#include "ConfigFromUiGenerator.hpp"
#include <mainwindow.h>

#include <QComboBox>

namespace Amb
{
    namespace Configs
    {
        ConfigFromUiGenerator::ConfigFromUiGenerator(const MainWindow *mainWindow,
                                                     const Amb::Ui::Module::Healer::HealerRulesTable &healerRulesTable,
                                                     const Amb::Ui::Module::Looter::LooterCategoriesTable &looterCategoriesTable,
                                                     const Amb::Ui::Module::Looter::LooterItemsTable &looterItemsTable)
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

        void ConfigFromUiGenerator::regenerateModule(Module::ModuleId moduleId)
        {
            switch (moduleId)
            {
                case Module::ModuleId::MOD_HEALER: regenerateHealer();
                case Module::ModuleId::MOD_LOOTER: regenerateLooter();
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

            const auto commonSettingsControls = mainWindow->getAdvancedSettingsCommon();
            auto selected = static_cast<size_t>(commonSettingsControls.captureMode->currentIndex());
            config.advancedSettings.common.captureMode.fromSize_t(selected);

            selected = static_cast<size_t>(commonSettingsControls.clientType->currentIndex());
            config.advancedSettings.common.clientType = Amb::Client::fromSize_t(selected);
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
            regenerateModule(Module::ModuleId::MOD_HEALER);
            regenerateModule(Module::ModuleId::MOD_LOOTER);
        }

        void ConfigFromUiGenerator::loadConfigFromString(const std::string &str)
        {
            auto newConfig = Amb::Configs::GlobalConfig::fromString(str);
            config.healerConfig = newConfig.healerConfig;
            config.advancedSettings = newConfig.advancedSettings;
            config.looter = newConfig.looter;
        }
    }
}
