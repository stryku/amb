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
    namespace Module
    {
        namespace Heal
        {
            class Healer : public ModuleCore
            {
            public:
                Healer(const Configs::HealerConfig &config,
                       const Configs::AdvancedSettings &advancedSettings,
                       Simulate::Simulator &simulator,
                       const Client::TibiaClientWindowInfo &tibiaClientWindowInfo);

                void setEnableDebugLogs(bool enabled) override;

            private:
                void executeRule(const Amb::Module::Heal::HealRule &rule);
                void runDetails() override;
                void applyConfigs() override;

                const Configs::HealerConfig &config;
                const Configs::AdvancedSettings &advancedSettings;
                Client::Reader::HealthManaReader healthManaReader;
                Client::Finder::HealthManaFinder healthManaFinder;
                Log::ImageConditionalLogger<Log::Condition::ImageLogOnceCondition> screenLogger;
            };
        }
    }
}
