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
        struct Image;
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
                    TibiaWindowsFinder(const Graphics::Image &screen);

                    std::vector<TibiaWindow> findAll(const RelativeRect &lastCapturedRect) const;
                    std::vector<TibiaItemsWindow> findMonsterLootWindows(const RelativeRect &lastCapturedRect) const;
                    std::vector<TibiaItemsWindow> findPlayerContainerWindows(const RelativeRect &lastCapturedRect,
                                                                             const std::vector<TibiaWindow>& allWindows) const;
                    std::vector<TibiaItemsWindow> findPlayerContainerWindows(const RelativeRect &lastCapturedRect) const;

                private:
                    boost::optional<TibiaWindow> findNextWindow(Rect &rect, const Graphics::Image &capturedStrip) const;
                    Rect createInitialWindowPatternRect(const RelativeRect &lastCapturedRect) const;
                    bool isMonsterLootWindow(const TibiaWindow &window) const;

                    const Graphics::Image& screen;
                };
            }
        }
    }
}
