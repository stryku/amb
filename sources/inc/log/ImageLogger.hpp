#pragma once

#include "log/Logger.hpp"
#include "utils/to_string/ImageToSimpleStringConverter.hpp"

namespace Amb
{
    namespace Log
    {
        using ImageLogger = Logger<Utils::ImageToSimpleStringConverter>;
    }
}
