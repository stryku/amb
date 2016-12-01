#pragma once

#include "ui/modules/healer/HealRule.hpp"
#include "client/reader/HealthManaReader.hpp"
#include "module/ModuleCore.hpp"
#include "Simulator.hpp"
#include "tibiareader.hpp"
#include "db/Items.hpp"

#include <chrono>

namespace Amb
{
    namespace Module
    {
        namespace Heal
        {
            class Healer : public ModuleCore
            {
            private:
                const Configs::HealerConfig &config;
                const Configs::AdvancedSettings &advancedSettings;
                Client::Reader::HealthManaReader healthManaReader;

                void executeRule( const Amb::Module::Heal::HealRule &rule );
                //void setTibiaClientType(Client::TibiaClientType type) override;
                void runDetails() override;
                void applyConfigs() override;


            public:
                Healer(const Configs::HealerConfig &config,
                       const Configs::AdvancedSettings &advancedSettings,
                       Simulate::Simulator &simulator,
                       const Client::TibiaClientWindowInfo &tibiaClientWindowInfo);
            };
        }
    }
}
