#pragma once

#include "ui/modules/healer/HealRule.hpp"
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
                Db::Items items;
                Readers::details::TibiaReader reader;

                const Configs::HealerConfig &config;
                const Configs::AdvancedSettings &advancedSettings;

                void executeRule( const Amb::Module::Heal::HealRule &rule );

                void runDetails();
                void applyConfigs();

            public:
                Healer(const Configs::HealerConfig &config,
                       const Configs::AdvancedSettings &advancedSettings,
                       Simulate::Simulator &simulator);
                ~Healer()
                {}

                void attachToNewWindow(HWND hwnd)
                {
                    reader.attachToNewWindow(hwnd);
                }
            };
        }
    }
}
