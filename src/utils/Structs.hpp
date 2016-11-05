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

        void toPropertyTreeBuilder(Utils::PropertyTreeBuilder &builder, const std::string &path = "") const
        {
            const auto elements =
            {
                Utils::PtreeElement<>{ path + ".from", utils::toString(from) },
                Utils::PtreeElement<>{ path + ".to", utils::toString(to) }
            };

            builder.addElements(elements);
        }

        static FromTo fromPtree(boost::property_tree::ptree &tree)
        {
            FromTo ret;

            ret.from = tree.get<int>("from");
            ret.to = tree.get<int>("to");

            return ret;
        }
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
