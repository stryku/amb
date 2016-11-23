#include "capture/DeadCreatureWindowFinder.hpp"
#include "graphics/Image.hpp"
#include "capture/ConstPixels.hpp"

namespace Amb
{
    namespace Capture
    {
        DeadCreatureWindowFinder::DeadCreatureWindowFinder(const Graphics::Image &screen)
            : screen{ screen }
        {}

        std::vector<Pos> DeadCreatureWindowFinder::find() const
        {
            std::vector<Pos> ret;
            Pos pos{ 1186 + 20, 257 + 10 };
            const auto maxY = screen.h - 32;

            while (pos.y < maxY)
            {
                const auto sprite = screen.getSprite(pos.x, pos.y, 28, 1);
                if (sprite == ConstPixels::Dead || sprite == ConstPixels::Slain)
                {
                    ret.emplace_back(Pos{ pos.x - 20, pos.y - 10 });
                    pos.y += 59;
                }
                ++pos.y;
            }

            return ret;
        }

    }
}