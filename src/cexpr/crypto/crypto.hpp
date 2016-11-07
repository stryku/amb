#pragma once

#include "cexpr/crypto/detail/detail.hpp"

#include <stdint.h>

namespace cexpr
{
    constexpr detail::hash_t hash(const uint8_t* begin, 
                                  const uint8_t* end)
    {
        return detail::hash(begin, end);
    }

    constexpr detail::hash_t hash(const char* str)
    {
        return detail::hash(str);
    }
}
