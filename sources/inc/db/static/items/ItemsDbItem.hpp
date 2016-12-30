#pragma once

#include "cexpr/crypto.hpp"

#include <string>
#include <vector>

namespace Amb
{
    namespace Db
    {
        namespace Static
        {
            namespace Items
            {
                struct Item
                {
                    std::string name;
                    std::vector<cexpr::hash_t> hashes;

                    bool isValid() const
                    {
                        return !name.empty();
                    }
                };
            }
        }
    }
}
