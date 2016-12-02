#include "client/window/finder/TibiaWindowsFinder.hpp"
#include "client/window/TibiaItemsWindow.hpp"
#include "capture/ConstPixels.hpp"

namespace Amb
{
    namespace Client
    {
        namespace Window
        {
            namespace Finder
            {
                std::vector<TibiaWindow> TibiaWindowsFinder::findAll(const RelativeRect &lastCapturedRect) const
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

                std::vector<TibiaItemsWindow> TibiaWindowsFinder::findMonsterLootWindows(const RelativeRect &lastCapturedRect) const
                {
                    constexpr Pos patternOffsetFromWindow{ 20,10 };
                    constexpr Size patternSize{ 28,1 };

                    const auto allWindows = findAll(lastCapturedRect);

                    std::vector<TibiaItemsWindow> monsterLootWindows;

                    for (const auto &window : allWindows)
                    {
                        const Rect rect{ window.rect.x + patternOffsetFromWindow.x,
                                         window.rect.y + patternOffsetFromWindow.y,
                                         patternSize.w,
                                         patternSize.h };

                        const auto sprite = screen.getSprite(rect);

                        if (sprite == ConstPixels::Dead || sprite == ConstPixels::Slain)
                            monsterLootWindows.emplace_back(window);
                    }

                    return monsterLootWindows;
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
