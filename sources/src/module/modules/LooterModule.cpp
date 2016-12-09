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
                        moveItems(monsterWindows[0], playerWindows[0], lastCapturedRect);
                    }
                }

            }

            void LooterModule::applyConfigs()
            {
                frameCapturer.setCaptureMode(advancedSettings.common.captureMode.mode);
            }

            void LooterModule::moveItems(const Client::Window::TibiaItemsWindow &from,
                                         const Client::Window::TibiaItemsWindow &to,
                                         const RelativeRect &capturedRect)
            {
                auto fromPos = Pos{ from.rect.x + 20, from.rect.y + 20 };
                auto toPos = Pos{ to.rect.x + 20, to.rect.y + 20 };

                fromPos = capturedRect.relativeToThis(fromPos);
                toPos = capturedRect.relativeToThis(toPos);

                for (const auto &item : from.items)
                {
                    mouseSimulator.dragAndDrop(fromPos, toPos);
                    //std::this_thread::sleep_for(std::chrono::milliseconds{ 400 });
                }
            }

        }
    }
}


