#pragma once

#include <string>

namespace Amb
{
    namespace Mouse
    {
        class MouseEvent
        {
        public:
            enum class KnownMouseEvents
            {
                LEFT_UP,
                LEFT_DOWN,
                RIGHT_UP,
                RIGHT_DOWN,
                WHEEL,
                X1_UP,
                X1_DOWN,
                X2_UP,
                X2_DOWN,

                UNDEF
            };

            MouseEvent() = default;
            MouseEvent(size_t v)
                : value{ v }
            {}

            std::string toString() const;
            static MouseEvent fromString(const std::string& str);
            static MouseEvent fromPrettyString(const std::string& str);
            std::string toPrettyString() const;

            static MouseEvent LeftUp() { return MouseEvent{ static_cast<size_t>(KnownMouseEvents::LEFT_UP) }; }
            static MouseEvent LeftDown() { return MouseEvent{ static_cast<size_t>(KnownMouseEvents::LEFT_DOWN) }; }
            static MouseEvent RightUp() { return MouseEvent{ static_cast<size_t>(KnownMouseEvents::RIGHT_UP) }; }
            static MouseEvent RightDown() { return MouseEvent{ static_cast<size_t>(KnownMouseEvents::RIGHT_DOWN) }; }
            static MouseEvent Wheel() { return MouseEvent{ static_cast<size_t>(KnownMouseEvents::WHEEL) }; }
            static MouseEvent X1Up() { return MouseEvent{ static_cast<size_t>(KnownMouseEvents::X1_UP) }; }
            static MouseEvent X1Down() { return MouseEvent{ static_cast<size_t>(KnownMouseEvents::X1_DOWN) }; }
            static MouseEvent X2Up() { return MouseEvent{ static_cast<size_t>(KnownMouseEvents::X2_UP) }; }
            static MouseEvent X2Down() { return MouseEvent{ static_cast<size_t>(KnownMouseEvents::X2_DOWN) }; }
            static MouseEvent Undef() { return MouseEvent{ static_cast<size_t>(KnownMouseEvents::UNDEF) }; }

            bool operator==(const MouseEvent& rhs) const
            {
                return value == rhs.value;
            }

            bool operator!=(const MouseEvent& rhs) const
            {
                return !(*this == rhs);
            }

        private:
            size_t value{ static_cast<size_t>(KnownMouseEvents::UNDEF) };
        };

       /* enum class MouseEvent
        {
            LEFT_UP,
            LEFT_DOWN,
            RIGHT_UP,
            RIGHT_DOWN,
            WHEEL,
            X1_UP,
            X1_DOWN,
            X2_UP,
            X2_DOWN,


            UNDEF
        };*/
/*
        std::string mouseEventToString(MouseEvent ev);
        std::string mouseEventToPrettyString(MouseEvent ev);

        MouseEvent fromPrettyString(const std::string& str);*/
    }
}
