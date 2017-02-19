#pragma once

#include "utils.hpp"
#include "graphics/Image.hpp"

#include <string>

namespace Amb
{
    namespace Utils
    {
        struct ImageToSimpleStringConverter
        {
            static auto convert(const Graphics::Image& img)
            {
                return std::to_string(img.w) + " " + Utils::imageToSimpleString(img);
            }
        };
    }
}
