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
                std::vector<TibiaWindow> TibiaWindowsFinder::findAll(const RelativeRect &lastCapturedRect)
                {
                    auto rect = createInitialWindowPatternRect(lastCapturedRect);

                    std::vector<TibiaWindow> windows;
                    TibiaWindow window;

                    while (boost::optional<TibiaWindow> foundWindow = findNextWindow(rect, screen))
                        windows.push_back(foundWindow.get());

                    return windows;
                }

                Rect TibiaWindowsFinder::createInitialWindowPatternRect(const RelativeRect &lastCapturedRect) const
                {
                    RelativeRect rect;

                    rect.rect.w = TibiaWindow::PatternSize.w;
                    rect.rect.h = TibiaWindow::PatternSize.h;
                    rect.rect.x = TibiaWindow::BeginOfWindowPatternOffset.x - TibiaWindow::Width;
                    rect.rect.y = TibiaWindow::BeginOfWindowPatternOffset.y;

                    return rect.relativeToRect(lastCapturedRect);
                }


                boost::optional<TibiaWindow> TibiaWindowsFinder::findNextWindow(Rect &rect, const Graphics::Image &capturedStrip) const
                {
                    TibiaWindow window;

                    for (; rect.y < screen.h - TibiaWindow::PatternSize.h; ++rect.y)
                    {
                        const auto sprite = capturedStrip.getSprite(rect);

                        if (sprite == TibiaWindow::BeginOfWindowPatternPixels)
                        {
                            window.rect.x = rect.x - TibiaWindow::BeginOfWindowPatternOffset.x;
                            window.rect.y = rect.y - TibiaWindow::BeginOfWindowPatternOffset.y;
                            rect.y += TibiaWindow::MinPixelsBetweenPatterns;
                        }
                        else if (sprite == TibiaWindow::EndOfWindowPatternPixels)
                        {
                            window.rect.h = rect.y + TibiaWindow::EndOfWindowPatternOffsetFromEnd.y - window.rect.y;
                            ++rect.y;
                            return window;
                        }
                    }

                    return{};
                }
                /*std::vector<MonsterLootWindow> TibiaWindowsFinder::findMonsterLootWindows()
                {}
                std::vector<PlayerContainerWindow> TibiaWindowsFinder::findPlayerContainerWindows()
                {}*/
            }
        }
    }
}
