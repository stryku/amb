#pragma once

#include <Windows.h>

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

                virtual void attachToNewProcess(DWORD pid) = 0;
                virtual size_t readCap() = 0;
            };
        }
    }
}
