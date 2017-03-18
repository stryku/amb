#pragma once

#include "hash/Hash.hpp"

#include <string>

namespace Amb
{
    namespace Db
    {
        namespace Static
        {
            namespace Containers
            {
                struct Item
                {
                    std::string name;
                    Hash::HashType iconHash;
                    Hash::HashType textHash;

                    inline bool isValid() const noexcept
                    {
                        return !name.empty();
                    }
                };
            }
        }
    }
}
