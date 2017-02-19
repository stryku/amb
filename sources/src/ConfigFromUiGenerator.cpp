#include "ConfigFromUiGenerator.hpp"
#include "log/log.hpp"

#include <mainwindow.h>

#include <QComboBox>

namespace Amb
{
    namespace Configs
    {
        ConfigFromUiGenerator::ConfigFromUiGenerator(const MainWindow *mainWindow,
                                                     const Client::TibiaClientWindowInfo &tibiaClientWindowInfo,
                                                     const Amb::Ui::Module::Healer::HealerRulesTable &healerRulesTable,
                                                     const Amb::Ui::Module::Looter::LooterCategoriesTable &looterCategoriesTable,
                                                     const Amb::Ui::Module::Looter::LooterItemsTable &looterItemsTable)
            : mainWindow{ mainWindow }
            , config{ tibiaClientWindowInfo }
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
#ifdef AMB_PRO_COMPILATION
                case Module::ModuleId::MOD_LOOTER: regenerateLooter();
#endif
            }
        }



        void ConfigFromUiGenerator::regenerateHealer()
        {
            LOG_DEBUG("regenerating healer config");
            config.healerConfig.rules = healerRulesTable.getRules();
        }
        
        void ConfigFromUiGenerator::regenerateLooter()
        {
            LOG_DEBUG("regenerating looter config");
            config.looter.categories = looterCategoriesTable.getCategories();
            config.looter.items = looterItemsTable.getItems();
        }

        void ConfigFromUiGenerator::regenerateAdvancedSettings()
        {
            LOG_DEBUG("ConfigFromUiGenerator::regenerateAdvancedSettings");
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

#ifdef AMB_PRO_COMPILATION
            regenerateModule(Module::ModuleId::MOD_LOOTER);
#endif
        }

        void ConfigFromUiGenerator::loadConfigFromString(const std::string &str, const Client::TibiaClientWindowInfo &info)
        {
            auto newConfig = Amb::Configs::GlobalConfig::fromString(str, info);
            config.healerConfig = newConfig.healerConfig;
            config.advancedSettings = newConfig.advancedSettings;
            config.looter = newConfig.looter;
        }
    }
}
