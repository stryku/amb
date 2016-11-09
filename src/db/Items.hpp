#pragma once

#include <cexpr/crypto.hpp>

#include <vector>
#include <array>
#include <map>
#include <string>

namespace AMB
{
    namespace Db
    {
        class Items
        {
        public:
            struct Item
            {
                std::string name;
                std::vector<cexpr::hash_t> hashes;

                bool isValid() const
                {
                    return !name.empty();
                }
            };

            Items();

            Item get(size_t id) const;
            Item get(const std::string &name) const;

            std::vector<std::string> getNames() const;

            size_t size() const
            {
                return map.size();
            }

        private:
            std::map<std::string, size_t> map;
        };
    }
}

