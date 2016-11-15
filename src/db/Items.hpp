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
            static const size_t BadId{ static_cast<size_t>(-1) };

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

            bool isThisEmpty(size_t id) const;

            Item get(size_t id) const;
            Item get(const std::string &name) const;
            size_t getIdByHash(const cexpr::hash_t &hash) const;

            std::vector<std::string> getNames() const;

            size_t size() const
            {
                return map.size();
            }

        private:
            std::map<std::string, size_t> map;
            std::map<cexpr::hash_t, size_t> hashMap;
        };
    }
}

