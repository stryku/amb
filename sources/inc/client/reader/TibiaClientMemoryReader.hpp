#pragma once

#include "client/reader/TibiaClientReader.hpp"

namespace Amb
{
    namespace Client
    {
        namespace Reader
        {
            class TibiaClientMemoryReader : public TibiaClientReader
            {
            public:
                size_t readCap() override;
            };
        }
    }
}

