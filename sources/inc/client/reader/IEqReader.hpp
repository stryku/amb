#pragma once

#include "client/EqItems.hpp"

namespace Amb
{
    namespace Client
    {
        namespace Reader
        {
            class IEqReader
            {
            public:
                virtual EqItems read() = 0;
            };
        }
    }
}
