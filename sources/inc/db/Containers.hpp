#pragma once

#include "db/static/containers/ContainersDbItem.hpp"

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
        class Containers
        {
        public:
            static const ItemId BadId{ static_cast<ItemId>(-1) };

            Containers();

            Static::Containers::Item get(ItemId id) const;
            Static::Containers::Item get(const std::string &name) const;
            ItemId getId(const std::string &name) const;
            ItemId getIdByHash(const cexpr::hash_t &hash) const;

            std::vector<std::string> getNames() const;

            size_t size() const
            {
                return nameToIdMap.size();
            }

        private:
            std::map<std::string, ItemId> nameToIdMap;
            std::map<cexpr::hash_t, ItemId> iconHashToId;
        };
    }
}

