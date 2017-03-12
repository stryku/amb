#pragma once

#include "utils/string/toString.hpp"

namespace Amb
{
    namespace Utils
    {
        struct SimpleToStringConverter
        {
            template <typename Type>
            static auto convert(const Type& type)
            {
                return utils::toString(type);
            }
        };
    }
}
