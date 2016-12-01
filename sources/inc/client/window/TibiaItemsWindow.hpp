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
                std::vector<Db::ItemId> items;
            };

            //using MonsterLootWindow = TibiaItemsWindow;
            //using PlayerContainerWindow = TibiaItemsWindow;
        }
    }
}
