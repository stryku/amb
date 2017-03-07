#pragma once

#include "utils/Structs.hpp"

#include <boost/optional.hpp>

namespace Amb
{
    namespace Client
    {
        namespace Finder
        {
            class GraphicEqFinder
            {
            public:
                boost::optional<Offset> find(/*const RelativeRect& lastCapturedRect*/);
            };
        }
    }
}
