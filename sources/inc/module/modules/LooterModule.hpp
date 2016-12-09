#pragma once

#include "ui/modules/healer/HealRule.hpp"
#include "module/ModuleCore.hpp"
#include "Simulator.hpp"
#include "tibiareader.hpp"
#include "db/Items.hpp"
#include "client/window/finder/TibiaWindowsFinder.hpp"
#include "capture/ItemsWindowReader.hpp"

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
                             const Client::TibiaClientWindowInfo &tibiaClientWindowInfo,
                             const Db::Items &itemsDb);

            private:
                Db::Items items;
                Client::Window::Finder::TibiaWindowsFinder windowsFinder;

                const Configs::Looter &config;
                const Configs::AdvancedSettings &advancedSettings;
                Capture::ItemsWindowReader itemsWindowReader;

                void runDetails() override;
                void applyConfigs() override;

                void moveItems(const Client::Window::TibiaItemsWindow &from, 
                               const Client::Window::TibiaItemsWindow &to,
                               const RelativeRect &capturedRect);
            };
        }
    }
}


