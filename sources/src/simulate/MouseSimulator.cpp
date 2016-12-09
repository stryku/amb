#include "utils/Structs.hpp"
#include "simulate/MouseSimulator.hpp"
#include "utils.hpp"


#include <chrono>
#include <thread>

namespace
{
    struct WindowsEventData
    {
        size_t event{ static_cast<size_t>(-1) };
        size_t btn{ 0 };

        WindowsEventData(Amb::Simulate::MouseSimulator::MouseEvent ev,
                         Amb::Simulate::MouseSimulator::Button button = Amb::Simulate::MouseSimulator::Button::LEFT)
        {
            switch (button)
            {
            case Amb::Simulate::MouseSimulator::Button::LEFT: btn = MK_LBUTTON;
                break;
            case Amb::Simulate::MouseSimulator::Button::RIGHT: btn = MK_RBUTTON;
                break;

            default: btn = 0;
                break;
            }

            switch (ev)
            {
            case Amb::Simulate::MouseSimulator::MouseEvent::DOWN: event = WM_LBUTTONDOWN;
                break;
            case Amb::Simulate::MouseSimulator::MouseEvent::UP: event = WM_LBUTTONUP;
                break;
            case Amb::Simulate::MouseSimulator::MouseEvent::MOVE: event = WM_MOUSEMOVE;
                break;

            default:
                assert(false);
                break;
            }
        }
    };

   /* auto getWindowsMouseEventData(Amb::Simulate::MouseSimulator::Button btn, bool down)
    {
        WindowsEventData data;

        switch (btn)
        {
            case Amb::Simulate::MouseSimulator::Button::LEFT: 
                data.event = down ? WM_LBUTTONDOWN : WM_LBUTTONUP;
                data.btn = MK_LBUTTON;
                break;

            case Amb::Simulate::MouseSimulator::Button::RIGHT:
                data.event = down ? WM_RBUTTONDOWN : WM_RBUTTONUP;
                data.btn = MK_RBUTTON;
                break;
        }

        return data;
    }*/

    void doEvent(HWND windowHandle, const Amb::Pos &pos, const WindowsEventData &data)
    {
        if (data.btn == -1)
            return;

        PostMessage(windowHandle, data.event, data.btn, MAKELPARAM(pos.x, pos.y));
    }
}

namespace Amb
{
    namespace Simulate
    {
        void MouseSimulator::attachToWindow(HWND hwnd)
        {
            windowHandler = hwnd;
        }

        void MouseSimulator::leftClick(const Pos &pos)
        {}
        void MouseSimulator::rightClick(const Pos &pos)
        {}
        void MouseSimulator::moveTo(const Pos &pos)
        {}
        void MouseSimulator::dragAndDrop(const Pos &from, const Pos &to)
        {
            static int delta = 1;
            const Amb::Utils::RandomBetween random = { 50,100 };

            POINT p;
            GetCursorPos(&p);

            down(from, Button::LEFT);
            std::this_thread::sleep_for(std::chrono::milliseconds{ random.get() });
            SetCursorPos(p.x, p.y + delta);
            std::this_thread::sleep_for(std::chrono::milliseconds{ random.get() });
            up(to, Button::LEFT);

            delta *= -1;
        }

        void MouseSimulator::down(const Pos &pos, Button btn)
        {
            doEvent(windowHandler, 
                    pos, 
                    WindowsEventData{ MouseEvent::DOWN, btn });
        }
        void MouseSimulator::up(const Pos &pos, Button btn)
        {
            doEvent(windowHandler, 
                    pos, 
                    WindowsEventData{ MouseEvent::UP, btn});
        }

        void MouseSimulator::move(const Pos &pos)
        {
            doEvent(windowHandler,
                    pos,
                    WindowsEventData{ MouseEvent::MOVE });
        }

        void MouseSimulator::click(const Pos &pos, Button btn)
        {
            const Amb::Utils::RandomBetween random{ 300, 500 };

            down(pos, btn);
            std::this_thread::sleep_for(std::chrono::milliseconds{ random.get() });
            up(pos, btn);
        }
    }
}
