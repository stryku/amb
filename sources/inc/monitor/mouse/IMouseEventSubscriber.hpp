#pragma once

#include "mouse/MouseEvent.hpp"

namespace Amb
{
    namespace Monitor
    {
        namespace Mouse
        {
            class IMouseEventPublisher;

            class IMouseEventSubscriber
            {
            public:
                virtual ~IMouseEventSubscriber() {}
                virtual void handle(Amb::Mouse::MouseEvent ev) = 0;
            };
        }
    }
}