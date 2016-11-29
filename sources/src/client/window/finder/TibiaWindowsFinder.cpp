#include "client/window/finder/TibiaWindowsFinder.hpp"
#include "client/window/TibiaItemsWindow.hpp"

namespace Amb
{
    namespace Client
    {
        namespace Window
        {
            namespace Finder
            {
                std::vector<TibiaWindow> TibiaWindowsFinder::findAll()
                {
                    std::vector<TibiaWindow> windows;
                    TibiaWindow window;

                    const auto x = screen.w - TibiaWindow::PatternsOffsetFromRight;
                    const auto strip = screen.getSprite(x,
                                                        0, 
                                                        TibiaWindow::PatternSize.w,
                                                        screen.h);

                    for (size_t y = 0; y < screen.h - TibiaWindow::PatternSize.h; ++y)
                    {
                        const auto sprite = strip.getSprite(0, y,
                                                            TibiaWindow::PatternSize.w,
                                                            TibiaWindow::PatternSize.h);

                        if (sprite == TibiaWindow::BeginOfWindowPatternPixels)
                        {
                            window.rect.x = x - TibiaWindow::BeginOfWindowPatternOffset.x;
                            window.rect.y = y - TibiaWindow::BeginOfWindowPatternOffset.y;
                            y += TibiaWindow::MinPixelsBetweenPatterns;
                        }
                        else if (sprite == TibiaWindow::EndOfWindowPatternPixels)
                        {
                            window.rect.h = y + TibiaWindow::EndOfWindowPatternOffsetFromEnd.y - window.rect.y;
                            windows.push_back(window);
                        }
                    }

                    return windows;
                }
                /*std::vector<MonsterLootWindow> TibiaWindowsFinder::findMonsterLootWindows()
                {}
                std::vector<PlayerContainerWindow> TibiaWindowsFinder::findPlayerContainerWindows()
                {}*/
            }
        }
    }
}
