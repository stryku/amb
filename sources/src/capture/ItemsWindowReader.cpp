#include "capture/ItemsWindowReader.hpp"
#include "graphics/Image.hpp"

namespace AMB
{
    namespace Capture
    {


        ItemWindow ItemsWindowReader::read(const Pos &pos) const
        {
            ItemWindow ret;

            ret.startPos = pos;
            const auto rows = countVisibleItemsRows(pos);
            ret.items = readItems(pos, rows);

            return ret;
        }

        size_t ItemsWindowReader::countVisibleItemsRows(const Pos &pos) const
        {
            const size_t headerSize{ 20 };
            const size_t rowHeight{ 36 };
            const size_t neededItemHeight{ 21 };
            auto height = readWindowHeight(pos);

            height -= headerSize;

            size_t rows = height / rowHeight;

            const size_t rest = height % rowHeight;

            if (rest >= neededItemHeight)
                ++rows;

            return rows;
        }

        std::vector<size_t> ItemsWindowReader::readItems(const Pos &pos, const size_t rows) const
        {
            const Pos rowOffset{ 12, 20 };
            const size_t offset{ 37 };
            Pos rowStart{ pos.x + rowOffset.x, pos.y + rowOffset.y };
            std::vector<size_t> items;

            for (size_t i = 0; i < rows; ++i)
            {
                for (size_t j = 0; j < 4; ++j)
                {
                    const auto itemId = itemCapturer.captureId({ static_cast<int>(rowStart.x + j *offset), 
                                                                 static_cast<int>(rowStart.y + i *offset) });

                    if (itemsDb.isThisEmpty(itemId))
                        return items;

                    items.emplace_back(itemId);
                }
            }

            return items;
        }

        size_t ItemsWindowReader::readWindowHeight(const Pos &startPos) const
        {
            Pos pos{ startPos.x + 45, startPos.y + 55 };
            const Rgba pattern{ 114,114,114,255 };
            Rgba px{ 0,0,0,0 };

            while (pos.y < screen.h)
            {
                px = screen.cpixel(pos.x, pos.y);

                if (px == pattern)
                    return pos.y - startPos.y;

                ++pos.y;
            }

            return static_cast<size_t>(-1);
        }
    }
}