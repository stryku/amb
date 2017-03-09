#include "monitor/mouse/MouseEventPublisher.hpp"
#include "monitor/mouse/IMouseEventSubscriber.hpp"

namespace Amb
{
    namespace Monitor
    {
        namespace Mouse
        {
            void MouseEventPublisher::registerSubscriber(IMouseEventSubscriber* sub)
            {
                std::lock_guard<std::mutex> lock{ mtx };

                if (subscribers.empty())
                    hook = SetWindowsHookEx(WH_MOUSE_LL, &lowLevelMouseProc, GetModuleHandle(0), 0);

                subscribers.push_back(sub);
            }

            void MouseEventPublisher::unregisterSubscriber(IMouseEventSubscriber* sub)
            {
                std::lock_guard<std::mutex> lock{ mtx };

                auto it = std::find(std::cbegin(subscribers), std::cend(subscribers), sub);

                if (it == std::cend(subscribers))
                    return;

                subscribers.erase(it);

                if (subscribers.empty())
                    UnhookWindowsHookEx(hook);
            }

            Amb::Mouse::MouseEvent MouseEventPublisher::translateToMouseKey(WPARAM wParam, LPARAM lParam)
            {
                Amb::Mouse::MouseEvent ev;

                switch (wParam)
                {
                    case WM_LBUTTONUP: return Amb::Mouse::MouseEvent::LEFT_UP;
                    case WM_RBUTTONUP: return Amb::Mouse::MouseEvent::RIGHT_UP;
                    case WM_XBUTTONUP: 
                    {
                        MSLLHOOKSTRUCT* data{ reinterpret_cast<MSLLHOOKSTRUCT*>(lParam) };

                        return (data->mouseData == 1) ? Amb::Mouse::MouseEvent::X1_UP
                                                        : Amb::Mouse::MouseEvent::X2_UP;
                    }
                    default: return Amb::Mouse::MouseEvent::UNDEF;
                }
            }

            LRESULT CALLBACK MouseEventPublisher::lowLevelMouseProc(int code, WPARAM wParam, LPARAM lParam)
            {
                if (code == HC_ACTION)
                {
                    const auto ev = translateToMouseKey(wParam, lParam);

                    if (ev != Amb::Mouse::MouseEvent::UNDEF)
                        publish(ev);
                }

                return CallNextHookEx(hook, code, wParam, lParam);
            }

            void MouseEventPublisher::publish(Amb::Mouse::MouseEvent ev)
            {
                std::lock_guard<std::mutex> lock{ mtx };

                for (auto sub : subscribers)
                    sub->handle(ev);
            }
        }
    }
}
