#pragma once

#include <functional>

namespace Amb
{
    namespace Monitor
    {
        namespace Mouse
        {
            class IMouseMonitor
            {
            public:
                virtual void start() = 0;
                virtual void stop() = 0;
                virtual void setCallback() = 0;
            };
        }
    }
}