#pragma once

#include "log/Logger.hpp"
#include "utils/to_string/RectToStringConverter.hpp"

namespace Amb
{
    namespace Log
    {
        using RectLogger = Logger<Utils::RectToStringConverter>;
    }
}
