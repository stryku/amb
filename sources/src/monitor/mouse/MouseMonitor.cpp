#include "monitor/mouse/MouseMonitor.hpp"
#include "monitor/mouse/IMouseEventPublisher.hpp"

namespace Amb
{
    namespace Monitor
    {
        namespace Mouse
        {
            MouseMonitor::MouseMonitor(IMouseEventPublisher& eventsPublisher)
                : eventsPublisher{ eventsPublisher }
            {}

            void MouseMonitor::start()
            {
                eventsPublisher.registerSubscriber(this);
            }

            void MouseMonitor::stop()
            {
                eventsPublisher.unregisterSubscriber(this);
            }

            void MouseMonitor::setCallback(Callback cb)
            {
                callback = cb;
            }
            void MouseMonitor::handle(Amb::Mouse::MouseEvent ev)
            {
                callback(ev);
            }
        }
    }
}
