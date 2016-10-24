#pragma once

#include <cstdint>

namespace AMB
{
    struct Pos
    {
        int x, y;
    };

    struct Size
    {
        size_t w, h;
    };

    struct Rect
    {
        int x, y;
        size_t w, h;
    };

    struct FromTo
    {
        int from, to;
    };

    struct Rgba
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        bool operator==(const Rgba& o) const
        {
            return o.r == r && o.g == g && o.b == b && o.a == a;
        }

        bool operator!=(const Rgba& o) const
        {
            return !(*this == o);
        }
    };
}
