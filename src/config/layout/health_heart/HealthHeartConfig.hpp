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
                    AMB::Size size;
                    size_t offsetFromRight;
                    size_t y;

                    std::array<AMB::Rgba, Static::pixelsSize> pixels;
                };
            }
        }
    }
}
