#pragma once

#include "cexpr/crypto/detail/detail.hpp"

#include <stdint.h>

namespace cexpr
{
    using hash_t = detail::hash_t;
    using hash_it = const uint8_t*;

    constexpr hash_t hash(const uint8_t* begin,
                                  const uint8_t* end)
    {
        return detail::hash(begin, end);
    }

    constexpr hash_t hash(const char* str)
    {
        return detail::hash(str);
    }
}
