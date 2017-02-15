#include "module/modules/LooterModule.hpp"
#include "client/window/TibiaItemsWindow.hpp"
#include "utils/random/RandomOffset.hpp"
#include "log/log.hpp"

#include <boost/range/adaptor/reversed.hpp>
#include <boost/assert.hpp>
#include <boost/utility/in_place_factory.hpp>

#include <chrono>

namespace Amb
{
    namespace Module
    {
        namespace Looter
        {
            LooterModule::LooterModule(const Configs::Looter &config,
                                       const Configs::AdvancedSettings &advancedSettings,
                                       Simulate::Simulator &simulator,
                                       const Client::TibiaClientWindowInfo &tibiaClientWindowInfo,
                                       Client::Window::Finder::DeadCreatureWindowFinderFactory&& factory,
                                       std::unique_ptr<Client::Reader::TibiaClientReader> tibiaClientReader)
                : ModuleCore{ simulator, tibiaClientWindowInfo, std::move(tibiaClientReader) }
                , windowsFinder{ screen }
                , config{ config }
                , advancedSettings{ advancedSettings }
                , itemsWindowReader{ screen, items }
                , deadCreatureWindowFinderFactory(std::move(factory))
                , unknowWindowsLogger{ "unknow_windows_logger", "logs/unknow_windows.txt" }
            {}

            void LooterModule::attachToNewProcess(DWORD pid)
            {
                BOOST_ASSERT_MSG(tibiaClientReader, "TibiaClientReader should be valid at this point!");
                LOG_DEBUG("LooterModule attaching to process: %d", pid);

                tibiaClientReader->attachToNewProcess(pid);
            }

            void LooterModule::setEnableDebugLogs(bool enabled)
            {
                LOG_DEBUG("LooterModule enabling debug logs: %s", enabled ? "true" : "false");
                itemsWindowReader.setEnableDebugLogs(enabled);
                unknowWindowsLogger.setExternalBool(enabled);
            }

            void LooterModule::runDetails()
            {
                BOOST_ASSERT_MSG(deadCreatureWindowFinder, "DeadCreatureWindowFinder should be valid at this point!");

                frameCapturer.captureRightStrip();
                const auto &lastCapturedRect = frameCapturer.getLastCaptureRect();
                const auto allPlayerWindows = windowsFinder.findAll(lastCapturedRect);
                auto monsterWindows = deadCreatureWindowFinder.get().find(allPlayerWindows, screen);

                if (!monsterWindows.empty())
                {
                    const auto playerWindows = windowsFinder.findPlayerContainerWindows(lastCapturedRect, allPlayerWindows);

                    if (!playerWindows.empty())
                    {
                        for (auto &monsterWindow : monsterWindows)
                        {
                            const auto items = itemsWindowReader.readItems(monsterWindow);
                            const auto lootableItemsPositions = findLootableItemsPositions(items);

                            if (!lootableItemsPositions.empty())
                            {
                                monsterWindow.items = items;
                                lootItemsFromWindow(lootableItemsPositions, 
                                                    monsterWindow, 
                                                    playerWindows, 
                                                    lastCapturedRect);
                                break;
                            }
                        }
                    }
                }

                std::this_thread::sleep_for(std::chrono::milliseconds{ 200 });
            }

            std::vector<size_t> LooterModule::findLootableItemsPositions(const std::vector<Db::ItemId> &items) const
            {
                std::vector<size_t> ret;

                for (size_t i = 0; i < items.size(); ++i)
                    if (lootableItem(items[i]))
                        ret.push_back(i);

                return ret;
            }

            void LooterModule::applyConfigs()
            {
                frameCapturer.setCaptureMode(advancedSettings.common.captureMode.mode);

                const auto clientType = advancedSettings.common.clientType;
                deadCreatureWindowFinder = boost::in_place(deadCreatureWindowFinderFactory.create(clientType)); //todo test this
            }

            boost::optional<Ui::Module::Looter::LootItem> LooterModule::findLootItemById(const Db::ItemId &id) const
            {
                const auto pred = [this, id](const Amb::Ui::Module::Looter::LootItem &item)
                {
                    const auto itemId = items.getId(item.name);
                    return itemId == id;
                };

                const auto found = std::find_if(std::cbegin(config.items),
                                                std::cend(config.items),
                                                pred);

                return (found != std::cend(config.items))
                        ? *found
                        : boost::optional<Ui::Module::Looter::LootItem>{};
            }

            bool LooterModule::haveEnoughCap(const Db::ItemId& id) const
            {
                const auto optionalItem = findLootItemById(id);

                if (!optionalItem)
                    return false;

                return haveEnoughCap(optionalItem.get());
            }

            bool LooterModule::haveEnoughCap(const Amb::Ui::Module::Looter::LootItem &item) const
            {
                return tibiaClientReader->readCap() >= item.minCap;
            }

            bool LooterModule::lootableItem(const Db::ItemId &id) const
            {
                return findLootItemById(id).is_initialized();
            }

            const Amb::Ui::Module::Looter::LootItem& LooterModule::findLootableItem(const Db::ItemId &id) const
            {
                const auto pred = [this, id](const Amb::Ui::Module::Looter::LootItem &item)
                {
                    const auto itemId = items.getId(item.name);
                    return itemId == id;
                };

                const auto found = std::find_if(std::cbegin(config.items),
                                                std::cend(config.items),
                                                pred);

                BOOST_ASSERT_MSG(found != std::cend(config.items), 
                                 "Item with id: %d not found! We should always find item in the list from gui", 
                                 id);

                return *found;
            }

            Pos LooterModule::findPosToMoveLootItem(const Db::ItemId &id, 
                                                    const std::vector<Client::Window::TibiaItemsWindow> &playerWindows) const
            {
                const auto& lootableItem = findLootableItem(id);
                const size_t containerIndex = lootableItem.category[0] - '0';
                size_t itemPos = 0;

                if(lootableItem.category.length() > 2)
                    itemPos = lootableItem.category[2] - '0';

                Pos pos = playerWindows[containerIndex].rect.pos();

                pos += playerWindows[containerIndex].itemOffset(itemPos);

                return pos;
            }

            void LooterModule::lootItemsFromWindow(const std::vector<size_t> &itemsPositions,
                                                   const Client::Window::TibiaItemsWindow &windowToLootFrom,
                                                   const std::vector<Client::Window::TibiaItemsWindow> &playerContainers,
                                                   const RelativeRect &capturedRect)
            { 
                static const Utils::Random::RandomOffset randomOffset{ 32, 32 };

                auto windowRelativePos = windowToLootFrom.itemPosition(0) + Pos::from(randomOffset.get());

                windowRelativePos = capturedRect.relativeToThis(windowRelativePos);

                for (auto itemPositionInWindow : boost::adaptors::reverse(itemsPositions))
                {
                    const auto &itemId = windowToLootFrom.items[itemPositionInWindow];

                    if (!haveEnoughCap(itemId))
                    {
                        LOG_DEBUG("No enough cap (%d) for item: %d", tibiaClientReader->readCap(), itemId);
                        continue;
                    }

                    const auto category = findLootableItemCategory(itemId);
                    auto toOptional = findCategoryDestinationPosition(category, playerContainers);

                    if (!toOptional)
                    {
                        LOG_DEBUG("Destination not found: %s", category.destination.c_str());
                        continue;
                    }

                    auto toPos = *toOptional;
                    toPos=  capturedRect.relativeToThis(toPos);

                    const auto fromPos = windowRelativePos + windowToLootFrom.itemOffset(itemPositionInWindow);
                    simulator.ctrlDown();
                    std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
                    mouseSimulator.dragAndDrop(fromPos, toPos);
                    std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
                    simulator.ctrlUp();
                }
            }

            const Amb::Ui::Module::Looter::Category LooterModule::findLootableItemCategory(const Db::ItemId &id) const
            {
                const auto &item = findLootableItem(id);
                const auto &categoryName = item.category;
                return config.findCategory(categoryName);
            }

            std::string LooterModule::findLootableItemDestination(const Db::ItemId &id) const
            {
                const auto itemLootCategory = findLootableItemCategory(id);
                return itemLootCategory.destination;
            }

            boost::optional<Pos> LooterModule::findCategoryDestinationPosition(const Amb::Ui::Module::Looter::Category &category,
                                                                               const std::vector<Client::Window::TibiaItemsWindow> &playerContainers) const
            {
                if (category.toOnto == Ui::Module::Looter::ToOnto::To)
                {
                    return findDestinationPosition(category.destination, playerContainers);
                }
                else
                {
                    const auto destinationContainerItemId = items.getByName(category.destination);

                    for (const auto &window : playerContainers)
                    {
                        const auto items = itemsWindowReader.readItems(window);
                        for (size_t i = 0; i < items.size(); ++i)
                            if (items[i] == destinationContainerItemId)
                                return window.itemPosition(i);
                    }

                    return{};
                }
            }

            boost::optional<Pos> LooterModule::findDestinationPosition(const std::string &destinationName,
                                                                       const std::vector<Client::Window::TibiaItemsWindow> &playerContainers) const
            {
                const auto destinationContainerDbItem = containersDb.get(destinationName);

                for (const auto &window : playerContainers)
                    if (window.icon.hash() == destinationContainerDbItem.iconHash)
                        return window.itemPosition(0);

                return{};
            }


        }
    }
}
