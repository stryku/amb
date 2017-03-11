#pragma once

#include "ui/modules/healer/HealRule.hpp"
#include "client/reader/HealthManaReader.hpp"
#include "client/finder/HealthManaFinder.hpp"
#include "module/ModuleCore.hpp"
#include "Simulator.hpp"
#include "tibiareader.hpp"
#include "db/Items.hpp"
#include "log/ImageConditionalLogger.hpp"
#include "log/condition/ImageLogOnceCondition.hpp"

#include <chrono>

namespace Amb
{
    namespace Config
    {
        namespace Module
        {
            struct HealerConfig;
            struct AdvancedSettingsConfig;
        }
    }

    namespace Module
    {
        namespace Heal
        {
            class Healer : public ModuleCore
            {
            public:
                Healer(const Config::Module::HealerConfig &config,
                       const Config::Module::AdvancedSettingsConfig &advancedSettings,
                       Simulate::Simulator &simulator,
                       const Client::TibiaClientWindowInfo &tibiaClientWindowInfo);

                void setEnableDebugLogs(bool enabled) override;
                void attachToNewWindow(HWND hwnd) override;

            private:
                void executeRule(const Amb::Module::Heal::HealRule &rule);
                void runDetails() override;
                void applyConfigs() override;

                const Config::Module::HealerConfig &config;
                const Config::Module::AdvancedSettingsConfig &advancedSettings;
                Client::Reader::HealthManaReader healthManaReader;
                Client::Finder::HealthManaFinder healthManaFinder;
                Log::ImageConditionalLogger<Log::Condition::ImageLogOnceCondition> screenLogger;
            };
        }
    }
}
