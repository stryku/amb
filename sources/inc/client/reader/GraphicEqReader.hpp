#pragma once

#include "client/reader/IEqReader.hpp"

namespace Amb
{
    namespace Client
    {
        namespace Reader
        {
            class GraphicEqReader : public IEqReader
            {
            public:
                EqItems read() override;
            };
        }
    }
}
