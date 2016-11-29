#pragma once

#include "utils/Structs.hpp"
#include "config/layout/health_heart/StaticValues.hpp"

#include <array>

namespace Amb
{
    namespace Config
    {
        namespace Layout
        {
            namespace HealthHeart
            {
                struct HealthHeartConfig
                {
                    Amb::Size size;
                    size_t offsetFromRight;
                    size_t y;

                    std::array<Amb::Rgba, Static::pixelsSize> pixels;
                };

                struct HealthHeartConfig_2
                {
                    RelativeRect rect;

                    std::array<Amb::Rgba, Static::pixelsSize> pixels;
                };
            }
        }
    }
}
