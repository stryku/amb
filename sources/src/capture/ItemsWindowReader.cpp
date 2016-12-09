#include "capture/ItemsWindowReader.hpp"
#include "graphics/Image.hpp"
#include "client/window/TibiaItemsWindow.hpp"

namespace Amb
{
    namespace Capture
    {
        ItemsWindowReader::ItemsWindowReader(const Graphics::Image &screen,
                                             const Db::Items &itemsDb)
            : screen{ screen }
            , itemsDb{ itemsDb }
            , itemCapturer{ screen, this->itemsDb }
        {}

        std::vector<Db::ItemId> ItemsWindowReader::readItems(const Client::Window::TibiaItemsWindow &window) const
        {
            const auto rows = countVisibleItemsRows(window.rect.pos());
            return readItems(window.rect.pos(), rows);
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
            const Pos rowStart{ pos.x + rowOffset.x, pos.y + rowOffset.y };
            std::vector<size_t> items;

            for (size_t i = 0; i < rows; ++i)
            {
                for (size_t j = 0; j < 4; ++j)
                {
                    const auto itemId = itemCapturer.captureId({ static_cast<int>(rowStart.x + j *offset), 
                                                                 static_cast<int>(rowStart.y + i *offset) });

                    if (itemId != Db::Items::BadId && itemsDb.isThisEmpty(itemId))
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

            while (pos.y < static_cast<int>(screen.h))
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