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

                        static constexpr Amb::Rgba firstPixel{ 79, 79, 211, 255 };
                        static constexpr Amb::Rgba otherPixels{ 79, 79, 219, 255 };
                    }

                    namespace ManaBar
                    {
                        static constexpr size_t manaBarOffsetFromHeartY_10 = 17;
                        static constexpr size_t manaBarOffsetFromHeartY_11 = 18;

                        static constexpr Amb::Rgba firstPixel{ 211, 79, 82, 255 };
                        static constexpr Amb::Rgba otherPixels{ 218, 80, 83, 255 };
                    };

                    static constexpr size_t maxLength = 87;
                    static constexpr size_t offsetFromHeartX = 17;
                }

                struct BarConfig
                {
                    Amb::Rgba firstPixel;
                    Amb::Rgba otherPixels;
                    Amb::Pos offsetFromHeart;
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
