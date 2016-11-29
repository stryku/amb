#pragma once

#include "graphics/Image.hpp"

namespace Amb
{
    namespace Client
    {
        namespace Window
        {
            struct TibiaWindow
            {
                static constexpr size_t MinPixelsBetweenPatterns = 43;
                static constexpr size_t PatternsOffsetFromRight = 14;
                static constexpr size_t Width = 175;
                static constexpr Size PatternSize = { 9,3 };

                static constexpr Pos BeginOfWindowPatternOffset = Pos{ 162, 5 };
                static constexpr std::array<Rgba, PatternSize.w*PatternSize.h> BeginOfWindowPatternPixels = { Rgba{ 36, 36, 36, 255 }, Rgba{ 47, 47, 47, 255 }, Rgba{ 38, 38, 38, 255 }, Rgba{ 108, 108, 108, 255 }, Rgba{ 181, 181, 181, 255 }, Rgba{ 181, 181, 181, 255 }, Rgba{ 92, 92, 92, 255 }, Rgba{ 39, 39, 39, 255 }, Rgba{ 34, 34, 34, 255 }, Rgba{ 52, 52, 52, 255 }, Rgba{ 46, 46, 46, 255 }, Rgba{ 101, 101, 101, 255 }, Rgba{ 176, 176, 176, 255 }, Rgba{ 108, 108, 108, 255 }, Rgba{ 133, 133, 133, 255 }, Rgba{ 174, 174, 174, 255 }, Rgba{ 82, 82, 82, 255 }, Rgba{ 42, 41, 41, 255 }, Rgba{ 43, 44, 43, 255 }, Rgba{ 102, 102, 102, 255 }, Rgba{ 175, 175, 175, 255 }, Rgba{ 104, 104, 104, 255 }, Rgba{ 50, 49, 48, 255 }, Rgba{ 49, 49, 49, 255 }, Rgba{ 131, 131, 131, 255 }, Rgba{ 174, 174, 174, 255 }, Rgba{ 86, 86, 86, 255 } };

                static constexpr Pos EndOfWindowPatternOffsetFromEnd = Pos{ 14, 12 };
                static constexpr std::array<Rgba, PatternSize.w*PatternSize.h> EndOfWindowPatternPixels = { Rgba{ 67, 67, 67, 255 }, Rgba{ 64, 64, 64, 255 }, Rgba{ 64, 64, 64, 255 }, Rgba{ 88, 88, 88, 255 }, Rgba{ 112, 112, 112, 255 }, Rgba{ 136, 136, 136, 255 }, Rgba{ 108, 108, 108, 255 }, Rgba{ 67, 67, 67, 255 }, Rgba{ 67, 67, 67, 255 }, Rgba{ 67, 67, 67, 255 }, Rgba{ 39, 39, 39, 255 }, Rgba{ 48, 48, 48, 255 }, Rgba{ 64, 64, 64, 255 }, Rgba{ 88, 88, 88, 255 }, Rgba{ 112, 112, 112, 255 }, Rgba{ 124, 124, 124, 255 }, Rgba{ 77, 77, 77, 255 }, Rgba{ 67, 67, 67, 255 }, Rgba{ 56, 56, 56, 255 }, Rgba{ 7, 7, 7, 255 }, Rgba{ 16, 16, 16, 255 }, Rgba{ 48, 48, 48, 255 }, Rgba{ 64, 64, 64, 255 }, Rgba{ 88, 88, 88, 255 }, Rgba{ 112, 112, 112, 255 }, Rgba{ 98, 98, 98, 255 }, Rgba{ 68, 68, 68, 255 } };

                static constexpr Rect IconRect = Rect{ 5,2, 11,11 };
                static constexpr Pos TitleOffset = Pos{ 20,10 };


                Graphics::Image icon;
                Graphics::Image title;
                Rect rect{ 0,0,175,0 };
            };
        }
    }
}
