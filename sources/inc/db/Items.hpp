#pragma once

#include <cexpr/crypto.hpp>

#include <vector>
#include <array>
#include <map>
#include <string>

namespace Amb
{
    namespace Db
    {
        using ItemId = size_t;
        class Items
        {
        public:
            static const ItemId BadId{ static_cast<ItemId>(-1) };

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

            bool isThisEmpty(ItemId id) const;

            Item get(ItemId id) const;
            Item get(const std::string &name) const;
            ItemId getIdByHash(const cexpr::hash_t &hash) const;

            std::vector<std::string> getNames() const;

            size_t size() const
            {
                return map.size();
            }

        private:
            std::map<std::string, ItemId> map;
            std::map<cexpr::hash_t, ItemId> hashMap;
        };
    }
}

