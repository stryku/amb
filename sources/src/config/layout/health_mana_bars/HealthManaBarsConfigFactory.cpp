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
                BarsConfig Factory::create(Amb::Client::TibiaClientType clientType) const
                {
                    BarsConfig config;

                    config.health.firstPixel = Static::HealthBar::firstPixel;
                    config.health.otherPixels = Static::HealthBar::otherPixels;
                    config.health.offsetFromHeart.x = Static::offsetFromHeartX;
                    config.health.maxLength = Static::maxLength;

                    config.mana.firstPixel = Static::ManaBar::firstPixel;
                    config.mana.otherPixels = Static::ManaBar::otherPixels;
                    config.mana.offsetFromHeart.x = Static::offsetFromHeartX;
                    config.mana.maxLength = Static::maxLength;

                    switch (clientType)
                    {
                        case Amb::Client::TibiaClientType::Tibia10:
                            config.health.offsetFromHeart.y = Static::HealthBar::healthBarOffsetFromHeartY_10;
                            config.mana.offsetFromHeart.y = Static::ManaBar::manaBarOffsetFromHeartY_10;
                        break;

                        case Amb::Client::TibiaClientType::Tibia11:
                            config.health.offsetFromHeart.y = Static::HealthBar::healthBarOffsetFromHeartY_11;
                            config.mana.offsetFromHeart.y = Static::ManaBar::manaBarOffsetFromHeartY_11;
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
