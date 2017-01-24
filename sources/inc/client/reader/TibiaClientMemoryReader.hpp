#pragma once

#include "client/reader/TibiaClientReader.hpp"
#include "memory/ProcessMemoryReader.hpp"

#include <Windows.h>

namespace Amb
{
    namespace Client
    {
        namespace Reader
        {
            class TibiaClientMemoryReader : public TibiaClientReader
            {
            public:
                TibiaClientMemoryReader(DWORD pid);

                void attachToNewProcess(DWORD pid) override;
                size_t readCap() override;

            private:
                Memory::ProcessMemoryReader processMemoryReader;
            };
        }
    }
}

