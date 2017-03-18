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

                LOG_DEBUG("MouseEventPublisher::registerSubscriber 0x{0:x}", reinterpret_cast<uintptr_t>(sub));

                if (subscribers.empty())
                    startListening();

                subscribers.push_back(sub);
            }

            void MouseEventPublisher::unregisterSubscriber(IMouseEventSubscriber* sub)
            {
                std::lock_guard<std::mutex> lock{ mtx };

                LOG_DEBUG("MouseEventPublisher::unregisterSubscriber 0x{0:x}", reinterpret_cast<uintptr_t>(sub));

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
                    case WM_LBUTTONUP: return Amb::Mouse::MouseEvent::LeftUp();
                    //case WM_LBUTTONDOWN: return Amb::Mouse::MouseEvent::LeftDown();
                    case WM_RBUTTONUP: return Amb::Mouse::MouseEvent::RightUp();
                    //case WM_RBUTTONDOWN: return Amb::Mouse::MouseEvent::RightDown();
                    /*case WM_XBUTTONDOWN:
                    {
                        MSLLHOOKSTRUCT* data{ reinterpret_cast<MSLLHOOKSTRUCT*>(lParam) };

                        return (GET_XBUTTON_WPARAM(data->mouseData) == 1) ? Amb::Mouse::MouseEvent::X1Down()
                                                                          : Amb::Mouse::MouseEvent::X2Down();
                    }*/
                    case WM_XBUTTONUP:
                    {
                        MSLLHOOKSTRUCT* data{ reinterpret_cast<MSLLHOOKSTRUCT*>(lParam) };

                        return (GET_XBUTTON_WPARAM(data->mouseData) == 1) ? Amb::Mouse::MouseEvent::X1Up()
                                                                          : Amb::Mouse::MouseEvent::X2Up();
                    }
                    default: return Amb::Mouse::MouseEvent::Undef();
                }
            }

            LRESULT CALLBACK MouseEventPublisher::lowLevelMouseProc(int code, WPARAM wParam, LPARAM lParam)
            {
                if (code == HC_ACTION)
                {
                    if (wParam != WM_MOUSEMOVE && wParam != WM_MOUSEFIRST)
                    {
                        const auto ev = translateToMouseKey(wParam, lParam);

                        if(ev != Amb::Mouse::MouseEvent::Undef())
                            publish(ev);
                    }
                }

                return CallNextHookEx(hook, code, wParam, lParam);
            }

            void MouseEventPublisher::publish(Amb::Mouse::MouseEvent ev)
            {
                std::lock_guard<std::mutex> lock{ mtx };

                LOG_DEBUG("MouseEventPublisher::publish {}", ev.toString());

                for (auto sub : subscribers)
                    sub->handle(ev);
            }


            void MouseEventPublisher::startListening()
            {
                LOG_DEBUG("MouseEventPublisher::startListening");
                hook = SetWindowsHookEx(WH_MOUSE_LL, &lowLevelMouseProc, GetModuleHandle(0), 0);
            }

            void MouseEventPublisher::stopListening()
            {
                LOG_DEBUG("MouseEventPublisher::stopListening");
                UnhookWindowsHookEx(hook);
            }
        }
    }
}
