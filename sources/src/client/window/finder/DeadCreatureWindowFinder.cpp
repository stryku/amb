#include "client/window/finder/DeadCreatureWindowFinder.hpp"
#include "graphics/Image.hpp"
#include "utils/Structs.hpp"
#include "client/window/TibiaItemsWindow.hpp"
#include "client/window/TibiaWindow.hpp"

namespace Amb
{

    namespace Client
    {
        namespace Window
        {
            namespace Finder
            {
                DeadCreatureWindowFinder::DeadCreatureWindowFinder(const PatternArray& slainPattern,
                                                                   const PatternArray& deadPattern,
                                                                   const PatternArray& remainsPattern)
                    : slainPattern{ slainPattern }
                    , deadPattern{ deadPattern }
                    , remainsPattern{ remainsPattern }
                {}

                Rect DeadCreatureWindowFinder::getPatternRectForWindow(const TibiaItemsWindow& window) const
                {
                    constexpr Offset PatternOffset{ 20, 10 };

                    Rect rect = window.rect + PatternOffset;
                    rect.w = 28;
                    rect.h = 1;

                    return rect;
                }


                std::vector<TibiaItemsWindow> DeadCreatureWindowFinder::find(const std::vector<TibiaWindow>& allFoundWindows,
                                                                             const Graphics::Image& rightStripSprite) const
                {

                    std::vector<TibiaItemsWindow> ret;
                    const auto maxY = rightStripSprite.h - 32;

                    for (const auto& window : allFoundWindows)
                    {
                        const auto patternRect = getPatternRectForWindow(window);
                        const auto sprite = rightStripSprite.getSprite(patternRect);

                        if (sprite == slainPattern ||
                            sprite == deadPattern ||
                            sprite == remainsPattern)
                        {
                            ret.push_back(window);
                        }
                    }

                    return ret;
                }
            }
        }
    }
}
