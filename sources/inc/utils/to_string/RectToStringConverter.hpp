#pragma once

#include "utils/Structs.hpp"

#include <string>

namespace Amb
{
    namespace Utils
    {
        struct RectToStringConverter
        {
            static auto convert(const Amb::Rect& rect)
            {
                return "x: " + std::to_string(rect.x) +
                       " y: " + std::to_string(rect.y) +
                       " w: " + std::to_string(rect.w) +
                       " h: " + std::to_string(rect.h);
            }
        };
    }
}
