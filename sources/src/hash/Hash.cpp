#include "hash/Hash.hpp"

namespace Amb
{
    namespace Hash
    {
        HashType hash(HashIt begin,
                      HashIt end,
                      HashType current_hash,
                      HashType prime)
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
