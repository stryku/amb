#pragma once

#include "utils/Structs.hpp"

#include <vector>

namespace AMB
{
    namespace Graphics
    {
        struct Image;
    }

    namespace Capture
    {
        class DeadCreatureWindowFinder
        {
        public:
            DeadCreatureWindowFinder(const Graphics::Image &screen);

            std::vector<Pos> find() const;

        private:
            const Graphics::Image &screen;
        };
    }
}
