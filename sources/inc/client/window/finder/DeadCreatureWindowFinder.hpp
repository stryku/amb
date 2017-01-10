#pragma once

#include <vector>
#include <array>

namespace Amb
{
    struct Rgba; 
    
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

                    std::vector<TibiaItemsWindow> find(const std::vector<TibiaWindow>& allFoundWindows,
                                                       const Graphics::Image& rightStripSprite);

                private:
                    Rect getPatternRectForWindow(const TibiaWindow& window) const;

                    const PatternArray& slainPattern;
                    const PatternArray& deadPattern;
                    const PatternArray& remainsPattern;
                };
            }
        }
    }
}
