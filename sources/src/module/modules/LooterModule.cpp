#include "module/modules/LooterModule.hpp"
#include "client/window/TibiaItemsWindow.hpp"
#include "utils/random/RandomOffset.hpp"

#include <boost/range/adaptor/reversed.hpp>

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
                                       const Client::TibiaClientWindowInfo &tibiaClientWindowInfo)
                : ModuleCore{ simulator, tibiaClientWindowInfo }
                , windowsFinder{ screen }
                , config{ config }
                , advancedSettings{ advancedSettings }
                , itemsWindowReader{ screen, items }
            {}

            void LooterModule::runDetails()
            {
                frameCapturer.captureRightStrip();
                const auto &lastCapturedRect = frameCapturer.getLastCaptureRect();
                auto monsterWindows = windowsFinder.findMonsterLootWindows(lastCapturedRect);

                if (!monsterWindows.empty())
                {
                    const auto playerWindows = windowsFinder.findPlayerContainerWindows(lastCapturedRect);

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

                for(size_t i = 0; i < items.size(); ++i)
                    if (lootableItem(items[i]))
                        ret.push_back(i);

                return ret;
            }

            void LooterModule::applyConfigs()
            {
                frameCapturer.setCaptureMode(advancedSettings.common.captureMode.mode);
            }

            bool LooterModule::lootableItem(const Db::ItemId &id) const
            {
                const auto pred = [this, id](const Amb::Ui::Module::Looter::LootItem &item)
                {
                    const auto itemId = items.getId(item.name);
                    return itemId == id;
                };

                const auto found = std::find_if(std::cbegin(config.items), 
                                                std::cend(config.items), 
                                                pred);

                return found != std::cend(config.items);
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

                if (found != std::cend(config.items))
                    return *found;
                else
                    assert(false);
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

                    const auto destinationName = findLootableItemDestination(itemId);
                    auto toOptional = findDestinationPosition(destinationName, playerContainers);

                    if (!toOptional)
                    {
                        qDebug("Destination not found: %s", destinationName.c_str());
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

            std::string LooterModule::findLootableItemDestination(const Db::ItemId &id) const
            {
                const auto &item = findLootableItem(id);
                const auto &categoryName = item.category;

                const auto pred = [&categoryName](const Amb::Ui::Module::Looter::Category &category)
                {
                    return categoryName == category.name;
                };

                const auto found = std::find_if(std::cbegin(config.categories),
                                                std::cend(config.categories),
                                                pred);

                if (found != std::cend(config.categories))
                    return found->destination;
                else
                    assert(false);
            }

            boost::optional<Pos> LooterModule::findDestinationPosition(const std::string &destinationName,
                                                                       const std::vector<Client::Window::TibiaItemsWindow> &playerContainers) const
            {
                const auto destinationContainerDbItem = containers.get(destinationName);

                for (const auto &window : playerContainers)
                    if (window.icon.hash() == destinationContainerDbItem.iconHash)
                        return window.itemPosition(0);

                return{};
            }


        }
    }
}
