#pragma once

#include <stdint.h>

namespace cexpr
{
    namespace detail
    {
        using hash_t = uint64_t;

        constexpr hash_t hash(const uint8_t* begin,
                              const uint8_t* end,
                              hash_t current_hash = 0xCBF29CE484222325ull,
                              hash_t prime = 0xCBF29CE484222325ull)
        {
            return begin != end
                   ? hash(begin + 1, end, current_hash ^ (*begin)*prime)
                   : current_hash;
        }

        constexpr hash_t hash(const char* str,
                              hash_t current_hash = 0xCBF29CE484222325ull,
                              hash_t prime = 0xCBF29CE484222325ull)
        {
            return *str
                   ? hash(str + 1, current_hash ^ (*str)*prime)
                   : current_hash;
        }
    }
}
