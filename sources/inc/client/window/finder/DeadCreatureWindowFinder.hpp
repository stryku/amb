#pragma once

#include <vector>
#include <array>

namespace Amb
{
    struct Rgba;
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

            namespace Finder
            {
                class DeadCreatureWindowFinder
                {
                private:
                    using PatternArray = const std::array<Rgba, 28>;

                public:
                    DeadCreatureWindowFinder(const PatternArray& slainPattern,
                                             const PatternArray& deadPattern,
                                             const PatternArray& remainsPattern);

                    DeadCreatureWindowFinder(DeadCreatureWindowFinder&&) = default;
                    DeadCreatureWindowFinder(const DeadCreatureWindowFinder&) = default;
                    DeadCreatureWindowFinder& operator=(DeadCreatureWindowFinder&&) = default;
                    DeadCreatureWindowFinder& operator=(const DeadCreatureWindowFinder&) = default;

                    std::vector<TibiaItemsWindow> find(const std::vector<TibiaWindow>& allFoundWindows,
                                                       const Graphics::Image& rightStripSprite) const;

                private:
                    Rect getPatternRectForWindow(const TibiaItemsWindow& window) const;

                    const PatternArray& slainPattern;
                    const PatternArray& deadPattern;
                    const PatternArray& remainsPattern;
                };
            }
        }
    }
}
