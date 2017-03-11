#include "module/modules/mlvl/MlvlModule.hpp"
#include "module/modules/mlvl/FoodEater.hpp"
#include "config/module/AdvancedSettingsConfig.hpp"

#include "log/log.hpp"

namespace Amb
{
    namespace Module
    {
        namespace Mlvl
        {
            MlvlModule::MlvlModule(const Configs::Mlvl &config,
                                   const Config::Module::AdvancedSettingsConfig &advancedSettings,
                                   Simulate::Simulator &simulator,
                                   const Client::TibiaClientWindowInfo &tibiaClientWindowInfo,
                                   std::unique_ptr<Client::Reader::TibiaClientReader> tibiaClientReader)
                : ModuleCore(simulator, tibiaClientWindowInfo, std::move(tibiaClientReader))
                , config{ config }
                , advancedSettings{ advancedSettings }
                , healthManaReader{ screen }
                , healthManaFinder{ tibiaClientWindowInfo }
                , screenLogger{ "mlvl_logger", "logs/mlvl.txt" }
                , antiIdler{ simulator }
            {}

            //void MlvlModule::attachToNewProcess(DWORD pid)
            //{}

            void MlvlModule::setEnableDebugLogs(bool enabled)
            {
                screenLogger.setExternalBool(enabled);
            }

            void MlvlModule::runDetails()
            {
                LOG_DEBUG("MlvlModule::runDetails");


                const int offsetFromRight = 176;
                RelativeRect captureRect;
                captureRect.relationPoint = tibiaClientWindowInfo.corners.topRight;
                captureRect.rect.x = -offsetFromRight;
                captureRect.rect.y = 0;
                captureRect.rect.w = offsetFromRight;
                captureRect.rect.h = tibiaClientWindowInfo.rect.h;

                frameCapturer.newFrame(captureRect.relativeToPoint(Pos{ 0,0 }));

                frameCapturer.captureRightStrip();

                if (!healthManaReader.isVisible(captureRect))
                {
                    LOG_DEBUG("Heart not on its place, refinding...");
                    const auto basicConfig = healthManaFinder.find(advancedSettings.common.clientType);
                    if (basicConfig)
                    {
                        const auto config = Config::Layout::HealthHeart::Factory{}.create_2(advancedSettings.common.clientType,
                                                                                            basicConfig.get());
                        healthManaReader.setHeartConfig(config);
                    }
                    else
                    {
                        LOG_DEBUG("Couldn't locate health and mana.");
                        LOG_DEBUG("Logging screen. It may take a while, please wait...");
                        screenLogger.log(screen);
                        return;
                    }
                }

                foodEater->eat();
                spellCaster->cast(captureRect);
                antiIdler.andiIdle();

                std::this_thread::sleep_for(std::chrono::seconds{ 1 });
            }

            void MlvlModule::applyConfigs()
            {
                foodEater = std::make_unique<FoodEater>(simulator, config.foodHotkey);
                spellCaster = std::make_unique<SpellCaster>(simulator,
                                                            healthManaReader,
                                                            config.spellHotkey,
                                                            config.manaPercentFrom,
                                                            config.manaPercentTo);

                healthManaReader.setTibiaClientType(advancedSettings.common.clientType);
                healthManaFinder.setCaptureMode(advancedSettings.common.captureMode.mode);
                frameCapturer.setCaptureMode(advancedSettings.common.captureMode.mode);
            }

            void MlvlModule::attachToNewWindow(HWND hwnd)
            {
                ModuleCore::attachToNewWindow(hwnd);
                healthManaFinder.attachToNewWindow(hwnd);
            }
        }
    }
}
