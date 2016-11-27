#pragma once

#include <vector>

namespace Amb
{
    namespace Client
    {
        namespace Window
        {
            struct TibiaWindow;
            struct TibiaItemsWindow;
            struct MonsterLootWindow;
            struct PlayerContainerWindow;

            namespace Finder
            {
                class TibiaWindowsFinder
                {
                public:
                    std::vector<TibiaWindow> findAll();
                    std::vector<MonsterLootWindow> findMonsterLootWindows();
                    std::vector<PlayerContainerWindow> findPlayerContainerWindows();
                };
            }
        }
    }
}
