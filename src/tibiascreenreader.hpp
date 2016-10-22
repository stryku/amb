#pragma once

#include "screencapturer.hpp"

#include <QtDebug>

namespace AMB
{
    namespace Readers
    {
        namespace details
        {
            class TibiaScreenReader
            {
            public:
                TibiaScreenReader(const Image &screen)
                    : screen{ screen }
                {}

                size_t getHpPercent() const
                {
                    qDebug(" TibiaScreenReader Reading hp\n");
                    return getPercent(hpInfo);
                }

                size_t getManaPercent() const
                {
                    return getPercent(manaInfo);
                }

                size_t isHearthVisible() const
                {
                    const Pos pos{ 1200, 149 };
                    const size_t a = 11;
                    const std::vector<Rgba> hearthPixels =
                    {
                        Rgba{ 70, 70, 70, 255 },
                        Rgba{ 70, 70, 70, 255 },
                        Rgba{ 73, 73, 73, 255 },
                        Rgba{ 70, 70, 70, 255 },
                        Rgba{ 71, 71, 71, 255 },
                        Rgba{ 54, 54, 118, 255 },
                        Rgba{ 65, 65, 64, 255 },
                        Rgba{ 63, 63, 62, 255 },
                        Rgba{ 69, 69, 68, 255 },
                        Rgba{ 70, 70, 70, 255 },
                        Rgba{ 70, 70, 70, 255 },
                        Rgba{ 70, 70, 69, 255 },
                        Rgba{ 74, 75, 74, 255 },
                        Rgba{ 68, 67, 68, 255 },
                        Rgba{ 76, 76, 76, 255 },
                        Rgba{ 64, 64, 84, 255 },
                        Rgba{ 93, 93, 183, 255 },
                        Rgba{ 61, 61, 81, 255 },
                        Rgba{ 68, 68, 68, 255 },
                        Rgba{ 69, 69, 70, 255 },
                        Rgba{ 68, 68, 68, 255 },
                        Rgba{ 70, 70, 70, 255 },
                        Rgba{ 77, 77, 77, 255 },
                        Rgba{ 73, 73, 73, 255 },
                        Rgba{ 65, 65, 85, 255 },
                        Rgba{ 73, 73, 73, 255 },
                        Rgba{ 97, 97, 180, 255 },
                        Rgba{ 113, 113, 221, 255 },
                        Rgba{ 97, 97, 180, 255 },
                        Rgba{ 74, 73, 73, 255 },
                        Rgba{ 65, 65, 84, 255 },
                        Rgba{ 66, 66, 65, 255 },
                        Rgba{ 71, 72, 71, 255 },
                        Rgba{ 71, 71, 71, 255 },
                        Rgba{ 68, 68, 71, 255 },
                        Rgba{ 60, 61, 89, 255 },
                        Rgba{ 107, 107, 211, 255 },
                        Rgba{ 125, 125, 255, 255 },
                        Rgba{ 125, 125, 255, 255 },
                        Rgba{ 125, 125, 255, 255 },
                        Rgba{ 107, 107, 211, 255 },
                        Rgba{ 57, 58, 85, 255 },
                        Rgba{ 70, 70, 73, 255 },
                        Rgba{ 67, 67, 67, 255 },
                        Rgba{ 69, 69, 69, 255 },
                        Rgba{ 57, 58, 85, 255 },
                        Rgba{ 86, 86, 193, 255 },
                        Rgba{ 113, 113, 251, 255 },
                        Rgba{ 113, 113, 255, 255 },
                        Rgba{ 113, 113, 255, 255 },
                        Rgba{ 113, 113, 255, 255 },
                        Rgba{ 113, 113, 251, 255 },
                        Rgba{ 87, 87, 193, 255 },
                        Rgba{ 58, 59, 87, 255 },
                        Rgba{ 67, 67, 67, 255 },
                        Rgba{ 56, 56, 103, 255 },
                        Rgba{ 91, 91, 219, 255 },
                        Rgba{ 97, 97, 241, 255 },
                        Rgba{ 97, 97, 241, 255 },
                        Rgba{ 97, 97, 241, 255 },
                        Rgba{ 97, 97, 241, 255 },
                        Rgba{ 97, 97, 241, 255 },
                        Rgba{ 97, 97, 241, 255 },
                        Rgba{ 97, 97, 241, 255 },
                        Rgba{ 91, 91, 219, 255 },
                        Rgba{ 55, 55, 103, 255 },
                        Rgba{ 64, 64, 124, 255 },
                        Rgba{ 79, 79, 211, 255 },
                        Rgba{ 79, 79, 219, 255 },
                        Rgba{ 79, 79, 219, 255 },
                        Rgba{ 79, 79, 219, 255 },
                        Rgba{ 79, 79, 219, 255 },
                        Rgba{ 79, 79, 219, 255 },
                        Rgba{ 79, 79, 219, 255 },
                        Rgba{ 79, 79, 219, 255 },
                        Rgba{ 79, 79, 211, 255 },
                        Rgba{ 64, 64, 124, 255 },
                        Rgba{ 85, 85, 125, 255 },
                        Rgba{ 96, 96, 192, 255 },
                        Rgba{ 64, 64, 192, 255 },
                        Rgba{ 64, 64, 192, 255 },
                        Rgba{ 64, 64, 192, 255 },
                        Rgba{ 64, 64, 192, 255 },
                        Rgba{ 64, 64, 192, 255 },
                        Rgba{ 64, 64, 192, 255 },
                        Rgba{ 64, 64, 192, 255 },
                        Rgba{ 64, 64, 192, 255 },
                        Rgba{ 63, 63, 123, 255 },
                        Rgba{ 64, 64, 94, 255 },
                        Rgba{ 160, 160, 201, 255 },
                        Rgba{ 78, 78, 176, 255 },
                        Rgba{ 51, 51, 167, 255 },
                        Rgba{ 51, 51, 167, 255 },
                        Rgba{ 51, 51, 167, 255 },
                        Rgba{ 51, 51, 167, 255 },
                        Rgba{ 51, 51, 167, 255 },
                        Rgba{ 51, 51, 167, 255 },
                        Rgba{ 51, 51, 167, 255 },
                        Rgba{ 66, 67, 96, 255 },
                        Rgba{ 59, 59, 67, 255 },
                        Rgba{ 107, 107, 148, 255 },
                        Rgba{ 167, 167, 201, 255 },
                        Rgba{ 46, 46, 144, 255 },
                        Rgba{ 46, 46, 144, 255 },
                        Rgba{ 52, 53, 94, 255 },
                        Rgba{ 46, 46, 144, 255 },
                        Rgba{ 46, 46, 144, 255 },
                        Rgba{ 46, 46, 144, 255 },
                        Rgba{ 54, 54, 102, 255 },
                        Rgba{ 64, 64, 72, 255 },
                        Rgba{ 68, 69, 68, 255 },
                        Rgba{ 54, 54, 84, 255 },
                        Rgba{ 83, 83, 122, 255 },
                        Rgba{ 65, 65, 131, 255 },
                        Rgba{ 55, 56, 89, 255 },
                        Rgba{ 56, 56, 56, 255 },
                        Rgba{ 54, 55, 88, 255 },
                        Rgba{ 65, 65, 131, 255 },
                        Rgba{ 65, 65, 131, 255 },
                        Rgba{ 60, 61, 88, 255 },
                        Rgba{ 71, 71, 71, 255 }
                    };

                    auto sprite = screen.getSprite(pos.x, pos.y, a, a);

                    return screen.getSprite(pos.x, pos.y, a, a) == hearthPixels;
                }

            private:
                struct HpManaInfo
                {
                    Rgba firstPixel;
                    Rgba otherPixels;
                    Pos pos;

                    static const size_t MaxLength = 1303 - 1216;
                };

                size_t getPercent(const HpManaInfo &info) const
                {
                    size_t px{ 0 };

                    if (screen.cpixel(info.pos.x, info.pos.y) != info.firstPixel)
                        return 0;

                    ++px;

                    while (screen.cpixel(info.pos.x + px, info.pos.y) == info.otherPixels && px < HpManaInfo::MaxLength)
                        ++px;

                    return px;
                }

                const HpManaInfo hpInfo = { Rgba{ 79, 79, 211, 255 }, Rgba{ 79, 79, 219, 255 }, Pos{ 1217, 153 } };
                const HpManaInfo manaInfo = { Rgba{ 211, 79, 82, 255 }, Rgba{ 218, 80, 83, 255 }, Pos{ 1217, 166} };
                const Image &screen;
            };
        }
    }
}
