#pragma once

#include "log/ImageLogger.hpp"
#include "log/ConditionalLogger.hpp"

#include <vector>

namespace Amb
{
    namespace Log
    {
        template <typename Condtion>
        using ImageConditionalLogger = ConditionalLogger<Condtion, ImageLogger, Graphics::Image>;
    }
}
