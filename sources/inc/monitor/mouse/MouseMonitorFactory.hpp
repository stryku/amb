#pragma once

#include "monitor/mouse/MouseEventPublisher.hpp"

#include <memory>

namespace Amb
{
    namespace Monitor
    {
        namespace Mouse
        {
            class IMouseMonitor;

            class MouseMonitorFactory
            {
            public:
                std::unique_ptr<IMouseMonitor> create();

            private:
                static MouseEventPublisher eventsPublisher;
            };
        }
    }
}