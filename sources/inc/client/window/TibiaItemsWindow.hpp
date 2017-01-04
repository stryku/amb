#pragma once

#include "client/window/TibiaWindow.hpp"
#include "db/Items.hpp"

namespace Amb
{
    namespace Client
    {
        namespace Window
        {
            struct TibiaItemsWindow : public TibiaWindow
            {
                TibiaItemsWindow() = default;
                TibiaItemsWindow(const TibiaWindow &window)
                    : TibiaWindow(window)
                {}

                std::vector<Db::ItemId> items;
                static constexpr Pos itemOffset(const size_t itemNumber)
                {
                    return Pos{ static_cast<int>((itemNumber % 4) * 37), 
                                static_cast<int>((itemNumber / 4) * 37) };
                }

                Pos itemPosition(const size_t itemNumber) const
                {
                    return rect.pos() + itemOffset(itemNumber);
                }
            };
        }
    }
}
