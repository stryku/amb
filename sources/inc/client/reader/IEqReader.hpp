#pragma once

#include "client/EqItems.hpp"

#include <boost/optional.hpp>

namespace Amb
{
    namespace Client
    {
        namespace Reader
        {
            class IEqReader
            {
            public:
                virtual boost::optional<EqItems> read() = 0;
            };
        }
    }
}
