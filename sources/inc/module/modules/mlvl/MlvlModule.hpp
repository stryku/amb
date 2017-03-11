#pragma once

#include "module/ModuleCore.hpp"
#include "client/reader/HealthManaReader.hpp"
#include "client/finder/HealthManaFinder.hpp"
#include "log/ImageConditionalLogger.hpp"
#include "log/condition/ImageLogOnceCondition.hpp"
#include "module/modules/mlvl/FoodEater.hpp"
#include "module/modules/mlvl/MlvlSpellCaster.hpp"
#include "module/modules/mlvl/AntiIdler.hpp"

namespace Amb
{
    namespace Config
    {
        namespace Module
        {
            struct AdvancedSettingsConfig;
        }
    }

    namespace Module
    {
        namespace Mlvl
        {
            class MlvlModule final : public ModuleCore
            {
            public:
                MlvlModule(const Configs::Mlvl &config,
                           const Config::Module::AdvancedSettingsConfig &advancedSettings,
                           Simulate::Simulator &simulator,
                           const Client::TibiaClientWindowInfo &tibiaClientWindowInfo,
                           std::unique_ptr<Client::Reader::TibiaClientReader> tibiaClientReader = nullptr);

                //void attachToNewProcess(DWORD pid) override;
                void setEnableDebugLogs(bool enabled) override;
                void attachToNewWindow(HWND hwnd) override;

            private:
                void runDetails() override;
                void applyConfigs() override;

                const Configs::Mlvl &config;
                const Config::Module::AdvancedSettingsConfig &advancedSettings;
                std::unique_ptr<Client::Reader::TibiaClientReader> tibiaClientReader;
                Client::Reader::HealthManaReader healthManaReader;
                Client::Finder::HealthManaFinder healthManaFinder;
                Log::ImageConditionalLogger<Log::Condition::ImageLogOnceCondition> screenLogger;
                AntiIdler antiIdler;
                std::unique_ptr<FoodEater> foodEater;
                std::unique_ptr<SpellCaster> spellCaster;
            };
        }
    }
}


