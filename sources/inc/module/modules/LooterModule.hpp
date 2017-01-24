﻿#pragma once

#include "ui/modules/healer/HealRule.hpp"
#include "module/ModuleCore.hpp"
#include "Simulator.hpp"
#include "tibiareader.hpp"
#include "db/Items.hpp"
#include "db/Containers.hpp"
#include "client/window/finder/TibiaWindowsFinder.hpp"
#include "client/window/finder/DeadCreatureWindowFinderFactory.hpp"
#include "client/window/finder/DeadCreatureWindowFinder.hpp"
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
                             Client::Window::Finder::DeadCreatureWindowFinderFactory&& factory,
                             std::unique_ptr<Client::Reader::TibiaClientReader> tibiaClientReader = nullptr);

                void attachToNewProcess(DWORD pid) override;

            private:
                Db::Items items;
                Db::Containers containersDb;
                Client::Window::Finder::TibiaWindowsFinder windowsFinder;
                boost::optional<Client::Window::Finder::DeadCreatureWindowFinder> deadCreatureWindowFinder;
                const Client::Window::Finder::DeadCreatureWindowFinderFactory deadCreatureWindowFinderFactory;

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
                bool haveEnoughCap(const Amb::Ui::Module::Looter::LootItem &item) const;
                bool haveEnoughCap(const Db::ItemId& id) const;
                boost::optional<Ui::Module::Looter::LootItem> findLootItemById(const Db::ItemId &id) const;

                std::string findLootableItemDestination(const Db::ItemId &id) const;
                const Amb::Ui::Module::Looter::Category findLootableItemCategory(const Db::ItemId &id) const;

                boost::optional<Pos> findCategoryDestinationPosition(const Amb::Ui::Module::Looter::Category &category,
                                                                     const std::vector<Client::Window::TibiaItemsWindow> &playerContainers) const;

                Pos findPosToMoveLootItem(const Db::ItemId &id, const std::vector<Client::Window::TibiaItemsWindow> &to) const;
                const Amb::Ui::Module::Looter::LootItem& findLootableItem(const Db::ItemId &id) const;
                std::vector<size_t> findLootableItemsPositions(const std::vector<Db::ItemId> &items) const;
                boost::optional<Pos> findDestinationPosition(const std::string &categoryName,
                                                             const std::vector<Client::Window::TibiaItemsWindow> &playerContainers) const;
            };
        }
    }
}


