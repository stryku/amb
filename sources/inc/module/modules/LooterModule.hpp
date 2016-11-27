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
        namespace Looter
        {
            class LooterModule : public ModuleCore
            {
            public:
                LooterModule(const Configs::Looter &config,
                             const Configs::AdvancedSettings &advancedSettings,
                             Simulate::Simulator &simulator);

                void attachToNewWindow(HWND hwnd);

            private:
                Db::Items items;
                Readers::details::TibiaReader reader;

                const Configs::Looter &config;
                const Configs::AdvancedSettings &advancedSettings;

                void runDetails();
                void applyConfigs();
            };
        }
    }
}


