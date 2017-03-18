#pragma once

#include "hash/Hash.hpp"

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
                    std::vector<Hash::HashType> hashes;

                    bool isValid() const
                    {
                        return !name.empty();
                    }
                };
            }
        }
    }
}
