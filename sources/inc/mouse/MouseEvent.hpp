#pragma once

#include <string>

namespace Amb
{
    namespace Mouse
    {
        enum class MouseEvent
        {
            LEFT_UP,
            LEFT_DOWN,
            RIGHT_UP,
            RIGHT_DOWN,
            WHEEL,
            X1_UP,
            X1_DOWN,
            X2_UP,
            X2_DOWN,


            UNDEF
        };

        std::string mouseEventToString(MouseEvent ev);
        std::string mouseEventToPrettyString(MouseEvent ev);
    }
}
