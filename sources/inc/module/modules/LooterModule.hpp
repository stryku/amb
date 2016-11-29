#pragma once

#include "ui/modules/healer/HealRule.hpp"
#include "module/ModuleCore.hpp"
#include "Simulator.hpp"
#include "tibiareader.hpp"
#include "db/Items.hpp"
#include "client/window/finder/TibiaWindowsFinder.hpp"

#include <chrono>

namespace Amb
{
    namespace Module
    {
        namespace Looter
        {
            class LooterModule final : public ModuleCore
            {
            public:
                LooterModule(const Configs::Looter &config,
                             const Configs::AdvancedSettings &advancedSettings,
                             Simulate::Simulator &simulator,
                             const Client::TibiaClientWindowInfo &tibiaClientWindowInfo);

                void attachToNewWindow(HWND hwnd);

            private:
                Db::Items items;
                Client::Window::Finder::TibiaWindowsFinder windowsFinder;
                //Readers::details::TibiaReader reader;

                const Configs::Looter &config;
                const Configs::AdvancedSettings &advancedSettings;

                void runDetails() override;
                void applyConfigs() override;
            };
        }
    }
}


