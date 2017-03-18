#pragma once

#include <stdint.h>

namespace Amb
{
    namespace Hash
    {
        using HashType = uint64_t;
        using HashIt = const uint8_t*;

        HashType hash(HashIt begin,
                      HashIt end,
                      HashType current_hash = 0xCBF29CE484222325ull,
                      HashType prime = 0xCBF29CE484222325ull);
    }
}
