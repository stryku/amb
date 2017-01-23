#pragma once

namespace Amb
{
    namespace Client
    {
        namespace Reader
        {
            class TibiaClientReader
            {
            public:
                virtual ~TibiaClientReader() = default;

                virtual size_t readCap() = 0;
            };
        }
    }
}
