#pragma once

#include "utils.hpp"
#include "graphics/Image.hpp"

namespace Amb
{
    namespace Utils
    {
        struct ImageToSimpleStringConverter
        {
            static auto convert(const Graphics::Image& img)
            {
                return Utils::imageToSimpleString(img);
            }
        };
    }
}
