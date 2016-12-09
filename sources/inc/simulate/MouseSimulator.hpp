#pragma once

#include <Windows.h>

namespace Amb
{
    struct Pos;

    namespace Simulate
    {
        class MouseSimulator
        {
        public:
            enum class Button
            {
                LEFT,
                RIGHT,
                NONE
            };

            enum class MouseEvent
            {
                DOWN,
                UP,
                MOVE
            };

            void leftClick(const Pos &pos);
            void rightClick(const Pos &pos);
            void moveTo(const Pos &pos);
            void dragAndDrop(const Pos &from, const Pos &to);

            void attachToWindow(HWND hwnd);

        private:
            void down(const Pos &pos, Button btn);
            void up(const Pos &pos, Button btn);
            void move(const Pos &pos);
            void click(const Pos &pos, Button btn);

            HWND windowHandler;
        };
    }
}