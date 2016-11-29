#pragma once

#include <vector>

namespace Amb
{
    namespace Graphics
    {
        class Image;
    }

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
                    TibiaWindowsFinder(const Graphics::Image &screen)
                        : screen{ screen }
                    {}

                    std::vector<TibiaWindow> findAll();/*
                    std::vector<MonsterLootWindow> findMonsterLootWindows();
                    std::vector<PlayerContainerWindow> findPlayerContainerWindows();*/

                private:
                    const Graphics::Image &screen;
                };
            }
        }
    }
}
