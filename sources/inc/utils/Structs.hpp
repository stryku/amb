#pragma once

#include "PropertyTreeBuilder.hpp"

#include <cstdint>
#include <functional>
#include <Windows.h>

namespace Amb
{
    namespace details
    {
        template <typename T>
        struct PosImpl
        {
            T x, y;
            bool operator==(const PosImpl &rhs) const
            {
                return x == rhs.x && y == rhs.y;
            }

            bool operator!=(const PosImpl &rhs) const
            {
                return !(*this == rhs);
            }

            PosImpl operator+(const PosImpl &rhs)
            {
                return PosImpl{ x + rhs.x, y + rhs.y };
            }

            PosImpl operator+(const PosImpl &rhs) const
            {
                return PosImpl{ x + rhs.x, y + rhs.y };
            }

            PosImpl& operator+=(const PosImpl &rhs)
            {
                x += rhs.x;
                y += rhs.y;
                return *this;
            }

            template <typename RhsPointType>
            static PosImpl from(const PosImpl<RhsPointType> &rhs)
            {
                return PosImpl{ static_cast<T>(rhs.x), static_cast<T>(rhs.y) };
            }
        };
    }

    using Pos = details::PosImpl<int>;
    using Offset = details::PosImpl<size_t>;

    struct Size
    {
        size_t w, h;
    };

    struct Rect
    {
        int x, y;
        size_t w, h;

        void setPos(Pos pos)
        {
            x = pos.x;
            y = pos.y;
        }

        bool operator==(const Rect &rhs) const
        {
            return x == rhs.x && y == rhs.y && w == rhs.w && h == rhs.h;
        }

        bool operator!=(const Rect &rhs) const
        {
            return !(*this == rhs);
        }

        static Rect fromWindowsRect(const RECT &rc)
        {
            Rect rect;

            rect.x = rc.left;
            rect.y = rc.top;
            rect.w = rc.right - rc.left;
            rect.h = rc.bottom - rc.top;

            return rect;
        }

        Pos topLeft() const
        {
            return Pos{ x, y };
        }

        Pos topRight() const
        {
            return Pos{ x + static_cast<int>(w), y };
        }

        Pos bottomLeft() const
        {
            return Pos{ x, y + static_cast<int>(h) };
        }

        Pos bottomRight() const
        {
            return Pos{ x + static_cast<int>(w), y + static_cast<int>(h) };
        }

        Pos pos() const
        {
            return topLeft();
        }

        Rect operator+(const Offset &pos) const
        {
            return *this + Pos::from(pos);
        }

        Rect operator+(const Pos &pos) const
        {
            Rect ret = *this;

            ret.x += pos.x;
            ret.y += pos.y;

            return ret;
        }
    };



    struct RectCorners
    {
        Pos topLeft;
        Pos topRight;
        Pos bottomLeft;
        Pos bottomRight;

        static RectCorners fromRect(const Rect &rc)
        {
            RectCorners ret;

            ret.bottomLeft = rc.bottomLeft();
            ret.bottomRight = rc.bottomRight();
            ret.topLeft = rc.topLeft();
            ret.topRight = rc.topRight();

            return ret;
        }
    };

    struct RelativeRect
    {
        Pos relationPoint;
        Rect rect;

        Rect relativeToRect(const RelativeRect &rhs) const
        {
            const auto rhsTopLeft = rhs.relativeToPoint(Pos{ 0,0 }).topLeft();
            Rect ret = relativeToPoint(Pos{ 0,0 });

            ret.x -= rhsTopLeft.x;
            ret.y -= rhsTopLeft.y;


            return ret;
        }
        Rect relativeToPoint(const Pos &point) const
        {
            Rect ret = rect;

            if (relationPoint != point)
            {
                ret.x += relationPoint.x - point.x;
                ret.y += relationPoint.y - point.y;
            }

            return ret;
        }

        Pos relativeToThis(const Pos &point) const
        {
            Pos ret = Pos{ relationPoint.x + rect.x, relationPoint.y + rect.y };;

            ret.x += point.x;
            ret.y += point.y;

            return ret;
        }
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
