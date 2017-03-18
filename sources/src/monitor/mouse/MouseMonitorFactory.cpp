#include "monitor/mouse/MouseMonitorFactory.hpp"
#include "monitor/mouse/MouseMonitor.hpp"

namespace Amb
{
    namespace Monitor
    {
        namespace Mouse
        {
            MouseEventPublisher MouseMonitorFactory::eventsPublisher;

            std::unique_ptr<IMouseMonitor> MouseMonitorFactory::create()
            {
                return std::unique_ptr<MouseMonitor>(new MouseMonitor(eventsPublisher));
            }
        }
    }
}
