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

                void lootItemsFromWindow(const std::vector<size_t> &itemsPositions,
                                         const Client::Window::TibiaItemsWindow &windowToLootFrom,
                                         const std::vector<Client::Window::TibiaItemsWindow> &playerContainers,
                                         const RelativeRect &capturedRect);

                bool lootableItem(const Db::ItemId &id) const;

                Pos findPosToMoveLootItem(const Db::ItemId &id, const std::vector<Client::Window::TibiaItemsWindow> &to) const;
                const Amb::Ui::Module::Looter::LootItem& findItem(const Db::ItemId &id) const;
                std::vector<size_t> findLootableItemsPositions(const std::vector<Db::ItemId> &items) const;
            };
        }
    }
}


