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
                TibiaItemsWindow(const TibiaWindow &window)
                    : TibiaWindow(window)
                {}

                std::vector<Db::ItemId> items;
            };
        }
    }
}

