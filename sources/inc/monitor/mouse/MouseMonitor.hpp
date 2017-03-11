#pragma once

#include "monitor/mouse/IMouseMonitor.hpp"
#include "monitor/mouse/IMouseEventSubscriber.hpp"

#include <memory>

#include <Windows.h>


namespace Amb
{
    namespace Monitor
    {
        namespace Mouse
        {
            class MouseMonitorFactory;
            class IMouseEventPublisher;

            class MouseMonitor : public IMouseMonitor, public IMouseEventSubscriber
            {
            public:
                MouseMonitor(const MouseMonitor&) = delete;
                MouseMonitor& operator=(const MouseMonitor&) = delete;

                MouseMonitor(MouseMonitor&&) = default;
                MouseMonitor& operator=(MouseMonitor&&) = default;


                void start() override;
                void stop() override;
                void setCallback(Callback cb) override;

                void handle(Amb::Mouse::MouseEvent ev) override;

            private:
                friend class MouseMonitorFactory;

                MouseMonitor(IMouseEventPublisher& eventsPublisher);

                Callback callback;
                IMouseEventPublisher& eventsPublisher;
            };
        }
    }
}
