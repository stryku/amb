#pragma once

#include "utils/Structs.hpp"

namespace Amb
{
    namespace Config
    {
        namespace Layout
        {
            namespace HealthManaBars
            {
                namespace Static
                {
                    namespace HealthBar
                    {
                        static constexpr size_t healthBarOffsetFromHeartY_10 = 4;
                        static constexpr size_t healthBarOffsetFromHeartY_11 = 5;

                        static constexpr AMB::Rgba firstPixel{ 79, 79, 211, 255 };
                        static constexpr AMB::Rgba otherPixels{ 79, 79, 219, 255 };
                    }

                    namespace ManaBar
                    {
                        static constexpr size_t manaBarOffsetFromHeartY_10 = 17;
                        static constexpr size_t manaBarOffsetFromHeartY_11 = 18;

                        static constexpr AMB::Rgba firstPixel{ 211, 79, 82, 255 };
                        static constexpr AMB::Rgba otherPixels{ 218, 80, 83, 255 };
                    };

                    static constexpr size_t maxLength = 87;
                    static constexpr size_t offsetFromHeartX = 17;
                }

                struct BarConfig
                {
                    AMB::Rgba firstPixel;
                    AMB::Rgba otherPixels;
                    AMB::Pos offsetFromHeart;
                    size_t maxLength;
                };

                struct BarsConfig
                {
                    BarConfig health;
                    BarConfig mana;
                };
            }
        }
    }

}
