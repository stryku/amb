#pragma once

#include "client/window/TibiaWindow.hpp"

#include <boost/optional.hpp>

#include <vector>

namespace Amb
{
    struct RelativeRect;
    struct Rect;

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

                    std::vector<TibiaWindow> findAll(const RelativeRect &lastCapturedRect) const;
                    std::vector<TibiaItemsWindow> findMonsterLootWindows(const RelativeRect &lastCapturedRect) const;
                    //std::vector<TibiaItemsWindow> findPlayerContainerWindows();

                private:
                    boost::optional<TibiaWindow> findNextWindow(Rect &rect, const Graphics::Image &capturedStrip) const;
                    Rect createInitialWindowPatternRect(const RelativeRect &lastCapturedRect) const;

                    const Graphics::Image &screen;
                };
            }
        }
    }
}
