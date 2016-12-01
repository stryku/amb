#include "module/modules/LooterModule.hpp"

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
                //, /*reader*/{ items }
                , windowsFinder{ screen }
                , config{ config }
                , advancedSettings{ advancedSettings }
            {}

            void LooterModule::runDetails()
            {
                const int offsetFromRight = 176;
                RelativeRect captureRect;
                captureRect.relationPoint = tibiaClientWindowInfo.corners.topRight;
                captureRect.rect.x = -offsetFromRight;
                captureRect.rect.y = 0;
                captureRect.rect.w = offsetFromRight;
                captureRect.rect.h = tibiaClientWindowInfo.rect.h;

                Client::Window::Finder::TibiaWindowsFinder finder(screen);
                frameCapturer.newFrame(captureRect.relativeToPoint(Pos{ 0,0 }));

                frameCapturer.captureRightStrip();

                auto windows = finder.findAll(frameCapturer.getLastCaptureRect());
            }

            void LooterModule::applyConfigs()
            {
                frameCapturer.setCaptureMode(advancedSettings.common.captureMode.mode);
            }
        }
    }
}


