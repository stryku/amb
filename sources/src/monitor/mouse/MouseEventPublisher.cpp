#include "monitor/mouse/MouseEventPublisher.hpp"
#include "monitor/mouse/IMouseEventSubscriber.hpp"
#include "log/log.hpp"

namespace Amb
{
    namespace Monitor
    {
        namespace Mouse
        {
            std::vector<IMouseEventSubscriber*> MouseEventPublisher::subscribers;
            HHOOK MouseEventPublisher::hook;
            std::mutex MouseEventPublisher::mtx;
            Utils::ThreadWorker MouseEventPublisher::peekThread;

            void MouseEventPublisher::registerSubscriber(IMouseEventSubscriber* sub)
            {
                std::lock_guard<std::mutex> lock{ mtx };

                if (subscribers.empty())
                    startListening();

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
                    stopListening();
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

                LOG_DEBUG("MouseEventPublisher::publish %d", static_cast<int>(ev));

                for (auto sub : subscribers)
                    sub->handle(ev);
            }


            void MouseEventPublisher::startListening()
            {
                hook = SetWindowsHookEx(WH_MOUSE_LL, &lowLevelMouseProc, GetModuleHandle(0), 0);
            }

            void MouseEventPublisher::stopListening()
            {
                UnhookWindowsHookEx(hook);
            }
        }
    }
}
