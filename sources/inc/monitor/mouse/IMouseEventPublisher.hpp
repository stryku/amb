#pragma once

namespace Amb
{
    namespace Monitor
    {
        namespace Mouse
        {
            class IMouseEventSubscriber;

            class IMouseEventPublisher
            {
            public:
                virtual ~IMouseEventPublisher() {}
                virtual void registerSubscriber(IMouseEventSubscriber* sub) = 0;
                virtual void unregisterSubscriber(IMouseEventSubscriber* sub) = 0;
            };
        }
    }
}