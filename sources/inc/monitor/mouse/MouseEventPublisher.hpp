#pragma once

#include "monitor/mouse/IMouseEventPublisher.hpp"
#include "mouse/MouseEvent.hpp"

#include <vector>
#include <mutex>

#include <Windows.h>

namespace Amb
{
    namespace Monitor
    {
        namespace Mouse
        {
            class MouseEventPublisher : public IMouseEventPublisher
            {
            public:
                void registerSubscriber(IMouseEventSubscriber* sub) override;
                void unregisterSubscriber(IMouseEventSubscriber* sub) override;

            private:
                static Amb::Mouse::MouseEvent translateToMouseKey(WPARAM wParam, LPARAM lParam);
                static LRESULT CALLBACK lowLevelMouseProc(int code, WPARAM wParam, LPARAM lParam);
                static void publish(Amb::Mouse::MouseEvent ev);

                static std::vector<IMouseEventSubscriber*> subscribers;
                static HHOOK hook;
                static std::mutex mtx;
            };
        }
    }
}