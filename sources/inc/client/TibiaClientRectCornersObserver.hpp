#pragma once

#include "utils/Structs.hpp"

namespace Amb
{
    namespace Client
    {
        class TibiaClientRectCornersObserver
        {
        public:
            void newClientRect(const Rect &rect)
            {
                corners.topLeft = rect.topLeft();
                corners.topRight = rect.topRight();
                corners.bottomLeft = rect.bottomLeft();
                corners.bottomRight = rect.bottomRight();
            }


            const RectCorners& getCorners() const
            {
                return corners;
            }

        private:
            RectCorners corners;
        };
    }
}
