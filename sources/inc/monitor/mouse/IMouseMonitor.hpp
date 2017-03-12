#pragma once

#include "mouse/MouseEvent.hpp"

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
                using Callback = std::function<void(Amb::Mouse::MouseEvent key)>;

                virtual void start() = 0;
                virtual void stop() = 0;
                virtual void setCallback(Callback cb) = 0;
            };
        }
    }
}