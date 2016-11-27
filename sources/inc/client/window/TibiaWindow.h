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
                Graphics::Image icon;
                Graphics::Image title;
                Rect rect;
            };
        }
    }
}
