#pragma once

#include <stdint.h>

namespace Amb
{
    namespace Module
    {
        namespace Modules
        {
            namespace MouseHotkeys
            {
                union MonitorableMouseEvent
                {
                    uint32_t first;
                    uint32_t second;
                    uint64_t hash;
                };
            }
        }
    }
}
