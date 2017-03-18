#pragma once

#include "mouse/MouseEvent.hpp"
#include "utils/ThreadWorker.hpp"

#include <memory>

namespace Amb
{
    namespace Monitor
    {
        namespace Mouse
        {
            class IMouseMonitor;
            class MouseMonitorFactory;

            class SingleMouseEventMonitor
            {
            public:
                SingleMouseEventMonitor(MouseMonitorFactory& factory);
                ~SingleMouseEventMonitor();

                Amb::Mouse::MouseEvent get();

            private:
                std::unique_ptr<IMouseMonitor> mouseMonitor;
            };
        }
    }
}
