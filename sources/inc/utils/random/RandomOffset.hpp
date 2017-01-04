#pragma once

#include "utils/random/RandomBetween.hpp"
#include "utils/Structs.hpp"

namespace Amb
{
    namespace Utils
    {
        namespace Random
        {
            struct RandomOffset
            {
                RandomBetween x{ 0,0 };
                RandomBetween y{ 0,0 };

                RandomOffset() = default;
                RandomOffset(size_t w, size_t h)
                    : x{ 0, w }
                    , y{ 0, h }
                {}

                Offset get() const
                {
                    return Offset{ x.get(), y.get() };
                }
            };
        }
    }
}
