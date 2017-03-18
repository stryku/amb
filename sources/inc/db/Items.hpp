#pragma once

#include "db/static/items/ItemsDbItem.hpp"
#include "hash/Hash.hpp"

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

            Items();

            bool isThisEmpty(ItemId id) const;

            Static::Items::Item get(ItemId id) const;
            Static::Items::Item get(const std::string &name) const;
            ItemId getId(const std::string &name) const;
            ItemId getIdByHash(const Hash::HashType &hash) const;
            ItemId getByName(const std::string &name) const;

            std::vector<std::string> getNames() const;

            size_t size() const
            {
                return map.size();
            }

        private:
            std::map<std::string, ItemId> map;
            std::map<Hash::HashType, ItemId> hashMap;
        };
    }
}

