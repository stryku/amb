#include "module/modules/Healer.hpp"

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
                    //captureRect.relationPoint = tibiaClientWindowInfo.corners.topRight;
                    //frameCapturer.newFrame(captureRect.relativeToPoint(Pos{ 0,0 }));

                    qDebug("Heart not on its place, refinding...");
                    if (!healthManaReader.findHeart(captureRect))
                    {
                        qDebug("Couldn't locate health and mana status!");
                        return;
                    }
                }

                auto hp = healthManaReader.getHpPercent(captureRect);
                auto mana = healthManaReader.getManaPercent(captureRect);

                for (const auto &rule : config.rules)
                {
                    if (rule.passed(hp, mana))
                    {
                        qDebug("Rule passed");
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
                //, topRightCorner{ topRightCorner }
            {}

            void Healer::applyConfigs()
            {
                healthManaReader.setTibiaClientType(advancedSettings.common.clientType);
                frameCapturer.setCaptureMode(advancedSettings.common.captureMode.mode);
            }
        }
    }
}
