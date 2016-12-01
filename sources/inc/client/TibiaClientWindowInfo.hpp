#pragma once

#include "utils/Structs.hpp"

namespace Amb
{
    namespace Client
    {
        struct TibiaClientWindowInfo
        {
            Rect rect;
            Rect rectOnMonitors;
            RectCorners corners;

            static TibiaClientWindowInfo fromRectOnMonitors(const Rect &rc)
            {
                TibiaClientWindowInfo ret;

                ret.rectOnMonitors = rc;
                ret.rect = Rect{ 0,0,rc.w - rc.x, rc.h - rc.y };
                ret.corners = RectCorners::fromRect(ret.rect);

                return ret;
            }

            bool operator==(const TibiaClientWindowInfo &rhs) const
            {
                return rectOnMonitors == rhs.rectOnMonitors;
            }

            bool operator!=(const TibiaClientWindowInfo &rhs) const
            {
                return !(*this == rhs);
            }
        };
    }
}
