#pragma once

#include "utils/Structs.hpp"
#include "capture/ItemCapturer.hpp"
#include "db/Items.hpp"

namespace AMB
{
    namespace Capture
    {
        struct ItemWindow
        {
            Pos startPos;
            std::vector<size_t> items;
        };

        class ItemsWindowReader
        {
        public:
            ItemsWindowReader(const Graphics::Image &screen,
                              const Db::Items &itemsDb)
                : screen{ screen }
                , itemCapturer{ screen,itemsDb }
            {}

            ItemWindow read(const Pos &pos) const;

        private:
            size_t readWindowHeight(const Pos &pos) const;
            size_t countVisibleItemsRows(const Pos &pos) const;
            std::vector<size_t> readItems(const Pos &pos, const size_t rows) const;

            const Graphics::Image &screen;
            const Db::Items itemsDb;
            const ItemCapturer itemCapturer;
        };
    }
}
