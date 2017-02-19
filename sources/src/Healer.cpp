#include "module/modules/Healer.hpp"
#include "log/log.hpp"

namespace Amb
{
    namespace Module
    {
        namespace Heal
        {
            void Healer::executeRule(const Amb::Module::Heal::HealRule &rule)
            {
                simulator.hotkey(rule.hotkey, { static_cast<size_t>(advancedSettings.healer.sleepAfterHotkey.from),
                                                static_cast<size_t>(advancedSettings.healer.sleepAfterHotkey.to) });
            }

            void Healer::runDetails()
            {
                const auto sleepTo = std::chrono::system_clock::now() +
                    std::chrono::milliseconds(Utils::RandomBetween{ static_cast<size_t>(advancedSettings.healer.randBetweenChecks.from), 
                                                                    static_cast<size_t>(advancedSettings.healer.randBetweenChecks.to) }.get());

                const int offsetFromRight = 176;
                RelativeRect captureRect;
                captureRect.relationPoint = tibiaClientWindowInfo.corners.topRight;
                captureRect.rect.x = -offsetFromRight;
                captureRect.rect.y = 0;
                captureRect.rect.w = offsetFromRight;
                captureRect.rect.h = tibiaClientWindowInfo.rect.h;

                frameCapturer.newFrame(captureRect.relativeToPoint(Pos{ 0,0 }));

                if (!healthManaReader.isVisible(captureRect))
                {
                    LOG_DEBUG("Heart not on its place, refinding...");
                    const auto basicConfig = healthManaFinder.find(advancedSettings.common.clientType,
                                                              captureRect);
                    if (basicConfig)
                    {
                        const auto config = Config::Layout::HealthHeart::Factory{}.create_2(advancedSettings.common.clientType, 
                                                                                            basicConfig.get());
                        healthManaReader.setHeartConfig(config);
                    }
                    else
                    {
                        captureRect.relationPoint = tibiaClientWindowInfo.corners.topLeft;
                        captureRect.rect.x = 0;
                        captureRect.rect.y = 0;
                        captureRect.rect.w = tibiaClientWindowInfo.corners.bottomRight.x - tibiaClientWindowInfo.corners.bottomLeft.x;
                        captureRect.rect.h = tibiaClientWindowInfo.corners.bottomLeft.y - tibiaClientWindowInfo.corners.topLeft.y;

                        frameCapturer.newFrame(captureRect.rect);

                        LOG_DEBUG("Couldn't locate health and mana status! Trying brutefoce.");
                        const auto bruteForceResult = healthManaFinder.find(advancedSettings.common.clientType,
                                                                            captureRect);

                        if (bruteForceResult)
                        {
                            const auto config = Config::Layout::HealthHeart::Factory{}.create_2(advancedSettings.common.clientType,
                                                                                                bruteForceResult.get());
                            healthManaReader.setHeartConfig(config);
                        }
                        else
                        {
                            LOG_DEBUG("Couldn't locate health and mana after bruteforce.");
                            LOG_DEBUG("Logging screen. It may take a while, please wait...");
                            screenLogger.log(screen);
                            return;
                        }
                    }
                }

                auto hp = healthManaReader.getHpPercent(captureRect);
                auto mana = healthManaReader.getManaPercent(captureRect);

                for (const auto &rule : config.rules)
                {
                    if (rule.passed(hp, mana))
                    {
                        LOG_DEBUG("Rule passed");
                        executeRule(rule);
                    }
                }

                std::this_thread::sleep_until(sleepTo);
            }

            Healer::Healer(const Configs::HealerConfig &config,
                           const Configs::AdvancedSettings &advancedSettings,
                           Simulate::Simulator &simulator,
                           const Client::TibiaClientWindowInfo &tibiaClientWindowInfo)
                : ModuleCore{ simulator, tibiaClientWindowInfo }
                , config{ config }
                , advancedSettings{ advancedSettings }
                , healthManaReader{ screen }
                , healthManaFinder{ screen }
                //, topRightCorner{ topRightCorner }
                , screenLogger{ "not_found_heart_logger", "logs/heart_not_found.txt" }
            {}

            void Healer::applyConfigs()
            {
                healthManaReader.setTibiaClientType(advancedSettings.common.clientType);
                frameCapturer.setCaptureMode(advancedSettings.common.captureMode.mode);
            }

            void Healer::setEnableDebugLogs(bool enabled)
            {
                screenLogger.setExternalBool(enabled);
            }
        }
    }
}
