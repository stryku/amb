#include "module/modules/LooterModule.hpp"
#include "client/window/TibiaItemsWindow.hpp"

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
                                       const Db::Items &itemsDb)
                : ModuleCore{ simulator, tibiaClientWindowInfo }
                , windowsFinder{ screen }
                , config{ config }
                , advancedSettings{ advancedSettings }
                , itemsWindowReader{ screen, itemsDb }
            {}

            void LooterModule::runDetails()
            {
                frameCapturer.captureRightStrip();
                const auto &lastCapturedRect = frameCapturer.getLastCaptureRect();
                auto windows = windowsFinder.findAll(lastCapturedRect);
                auto playerWindows = windowsFinder.findPlayerContainerWindows(lastCapturedRect);
                auto monsterWindows = windowsFinder.findMonsterLootWindows(lastCapturedRect);

                if (!monsterWindows.empty() && !playerWindows.empty())
                {
                    monsterWindows[0].items = itemsWindowReader.readItems(monsterWindows[0]);
                    if (!monsterWindows[0].items.empty())
                    {
                        moveItems(monsterWindows[0], playerWindows, lastCapturedRect);
                    }
                }

                std::this_thread::sleep_for(std::chrono::milliseconds{ 200 });
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

            const Amb::Ui::Module::Looter::LootItem& LooterModule::findItem(const Db::ItemId &id) const
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
                const auto& lootableItem = findItem(id);
                const size_t containerIndex = lootableItem.category[0] - '0';
                size_t itemPos = 0;

                if(lootableItem.category.length() > 2)
                    itemPos = lootableItem.category[2] - '0';

                Pos pos = playerWindows[containerIndex].rect.pos();

                pos += playerWindows[containerIndex].itemOffset(itemPos);

                return pos;
            }

            void LooterModule::moveItems(const Client::Window::TibiaItemsWindow &from,
                                         const std::vector<Client::Window::TibiaItemsWindow> &playerContainers,
                                         const RelativeRect &capturedRect)
            {
                auto fromPos = Pos{ from.rect.x + 20, from.rect.y + 20 };

                fromPos = capturedRect.relativeToThis(fromPos);

                if (from.items.empty())
                    return;

                for(int i = from.items.size() - 1; i >= 0; --i)
                {
                    if (from.items[i] != Db::Items::BadId && lootableItem(from.items[i]))
                    {
                        auto toPos = findPosToMoveLootItem(from.items[i], playerContainers);
                        toPos = capturedRect.relativeToThis(toPos);

                        fromPos += from.itemOffset(i);
                        simulator.ctrlDown();
                        mouseSimulator.dragAndDrop(fromPos, toPos);
                        simulator.ctrlUp();
                    }
                }
            }

        }
    }
}


