#pragma once

#include "config/layout/health_mana_bars/HealthManaBarsConfigFactory.hpp"
#include "config/layout/health_mana_bars/HealthManaBars.hpp"

namespace Amb
{
    namespace Config
    {
        namespace Layout
        {
            namespace HealthManaBars
            {
                BarsConfig Factory::create(Amb::Client::TibiaClientType clientType, bool isSmall) const
                {
                    BarsConfig config;

                    if (isSmall)
                    {
                        config.health.firstPixel = Static::HealthBar::firstPixel;
                        config.health.otherPixels = Static::HealthBar::otherPixels;
                        config.mana.firstPixel = Static::ManaBar::firstPixel;
                        config.mana.otherPixels = Static::ManaBar::otherPixels;
                        config.health.offsetFromHeart.x = Static::offsetFromHeartX;
                        config.mana.offsetFromHeart.x = Static::offsetFromHeartX;
                        config.health.maxLength = Static::maxLength;
                        config.mana.maxLength = Static::maxLength;
                    }
                    else
                    {
                        config.health.firstPixel = Static::HealthBar::firstPixel_big;
                        config.health.otherPixels = Static::HealthBar::otherPixels_big;
                        config.mana.firstPixel = Static::ManaBar::firstPixel_big;
                        config.mana.otherPixels = Static::ManaBar::otherPixels_big;

                        config.health.offsetFromHeart.x = Static::offsetFromHeartX_big;
                        config.mana.offsetFromHeart.x = Static::offsetFromHeartX_big;
                        config.health.maxLength = Static::maxLength_big;
                        config.mana.maxLength = Static::maxLength_big;
                    }



                    switch (clientType)
                    {
                        case Amb::Client::TibiaClientType::Tibia10:
                        {
                            if (isSmall)
                            {
                                config.health.offsetFromHeart.y = Static::HealthBar::healthBarOffsetFromHeartY_10;
                                config.mana.offsetFromHeart.y = Static::ManaBar::manaBarOffsetFromHeartY_10;
                            }
                            else
                            {
                                config.health.offsetFromHeart.y = Static::HealthBar::healthBarOffsetFromHeartY_11_big;
                                config.mana.offsetFromHeart.y = Static::ManaBar::manaBarOffsetFromHeartY_11_big;
                            }
                        }
                        break;

                        case Amb::Client::TibiaClientType::Tibia11:
                        {
                            if (isSmall)
                            {
                                config.health.offsetFromHeart.y = Static::HealthBar::healthBarOffsetFromHeartY_11;
                                config.mana.offsetFromHeart.y = Static::ManaBar::manaBarOffsetFromHeartY_11;
                            }
                            else
                            {
                                config.health.offsetFromHeart.y = Static::HealthBar::healthBarOffsetFromHeartY_11_big;
                                config.mana.offsetFromHeart.y = Static::ManaBar::manaBarOffsetFromHeartY_11_big;
                            }
                        }
                        break;

                        case Amb::Client::TibiaClientType::Flash:
                        default:
                            assert(false);
                    }

                    return config;
                }
            }
        }
    }
}
