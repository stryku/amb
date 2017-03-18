#pragma once

#include <stdint.h>

namespace Amb
{
    namespace Hash
    {
        using hash_t = uint64_t;
        using hash_it = const uint8_t*;

        hash_t hash(const uint8_t* begin,
                    const uint8_t* end,
                    hash_t current_hash = 0xCBF29CE484222325ull,
                    hash_t prime = 0xCBF29CE484222325ull)
        {
            while (begin != end)
            {
                current_hash ^= (*begin)*prime;
                ++begin;
            }

            return current_hash;
        }
    }
}
