#pragma once

#include "utils/Structs.hpp"
#include "capture/ItemCapturer.hpp"
#include "db/Items.hpp"

namespace Amb
{
    namespace Client
    {
        namespace Window
        {
            struct TibiaItemsWindow;
        }
    }

    namespace Capture
    {
        class ItemsWindowReader
        {
        public:
            ItemsWindowReader(const Graphics::Image &screen,
                              const Db::Items &itemsDb);

            std::vector<Db::ItemId> readItems(const Client::Window::TibiaItemsWindow &window) const;
            void setEnableDebugLogs(bool enabled);

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
