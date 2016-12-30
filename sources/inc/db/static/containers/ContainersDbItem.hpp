#pragma once

#include "cexpr/crypto.hpp"

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
                    cexpr::hash_t iconHash;
                    cexpr::hash_t textHash;

                    inline bool isValid() const noexcept
                    {
                        return !name.empty();
                    }
                };
            }
        }
    }
}
