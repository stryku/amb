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
                auto itemWindows = windowsFinder.findPlayerContainerWindows(lastCapturedRect);
                //auto monsterWindows = windowsFinder.findMonsterLootWindows(lastCapturedRect);

                if (!itemWindows.empty())
                {
                    auto items = itemsWindowReader.readItems(itemWindows[0]);
                }
            }

            void LooterModule::applyConfigs()
            {
                frameCapturer.setCaptureMode(advancedSettings.common.captureMode.mode);
            }
        }
    }
}


