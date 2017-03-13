#include "monitor/mouse/SingleMouseEventMonitor.hpp"
#include "monitor/mouse/IMouseMonitor.hpp"
#include "monitor/mouse/MouseMonitorFactory.hpp"
#include "log/log.hpp"

namespace Amb
{
    namespace Monitor
    {
        namespace Mouse
        {
            SingleMouseEventMonitor::SingleMouseEventMonitor(MouseMonitorFactory& factory)
                : mouseMonitor{ factory.create() }
            {}
            SingleMouseEventMonitor::~SingleMouseEventMonitor() {}

            Amb::Mouse::MouseEvent SingleMouseEventMonitor::get()
            {
                LOG_DEBUG("SingleMouseEventMonitor::get starting");

                Amb::Mouse::MouseEvent retEv;
                bool stillWaiting{ true };

                auto cb = [&retEv, &stillWaiting](Amb::Mouse::MouseEvent ev)
                {
                    LOG_DEBUG("SingleMouseEventMonitor::get callback with ev: {}", Amb::Mouse::mouseEventToString(ev));
                    retEv = ev;
                    stillWaiting = false;
                };

                mouseMonitor->setCallback(cb);

                mouseMonitor->start();

                LOG_DEBUG("SingleMouseEventMonitor::get waiting...");
                while (stillWaiting)
                {
                    MSG msg;
                    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
                        DispatchMessage(&msg);
                }

                mouseMonitor->stop();

                LOG_DEBUG("SingleMouseEventMonitor::get returning {}", Amb::Mouse::mouseEventToString(retEv));

                return retEv;
            }
        }
    }
}
