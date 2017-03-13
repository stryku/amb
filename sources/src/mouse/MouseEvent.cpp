#include "mouse/MouseEvent.hpp"

namespace Amb
{
    namespace Mouse
    {
        std::string mouseEventToString(MouseEvent ev)
        {
            switch (ev)
            {
                case Amb::Mouse::MouseEvent::LEFT_UP: return "LEFT_UP";
                case Amb::Mouse::MouseEvent::LEFT_DOWN: return "LEFT_DOWN";
                case Amb::Mouse::MouseEvent::RIGHT_UP: return "RIGHT_UP";
                case Amb::Mouse::MouseEvent::RIGHT_DOWN: return "RIGHT_DOWN";
                case Amb::Mouse::MouseEvent::WHEEL: return "WHEEL";
                case Amb::Mouse::MouseEvent::X1_UP: return "X1_UP";
                case Amb::Mouse::MouseEvent::X1_DOWN: return "X1_DOWN";
                case Amb::Mouse::MouseEvent::X2_UP: return "X2_UP";
                case Amb::Mouse::MouseEvent::X2_DOWN: return "X2_DOWN";

                case Amb::Mouse::MouseEvent::UNDEF:
                default:
                    return "UNDEF";
            }
        }

        std::string mouseEventToPrettyString(MouseEvent ev)
        {
            switch (ev)
            {
                case Amb::Mouse::MouseEvent::LEFT_UP: return "Left button";
                case Amb::Mouse::MouseEvent::LEFT_DOWN: return "Left button down";
                case Amb::Mouse::MouseEvent::RIGHT_UP: return "Right button";
                case Amb::Mouse::MouseEvent::RIGHT_DOWN: return "Right button down";
                case Amb::Mouse::MouseEvent::WHEEL: return "Wheel";
                case Amb::Mouse::MouseEvent::X1_UP: return "X1 button";
                case Amb::Mouse::MouseEvent::X1_DOWN: return "X1 button down";
                case Amb::Mouse::MouseEvent::X2_UP: return "X2 button";
                case Amb::Mouse::MouseEvent::X2_DOWN: return "X2 button down";

                case Amb::Mouse::MouseEvent::UNDEF:
                default:
                    return "Undefined";
            }
        }
    }
}
