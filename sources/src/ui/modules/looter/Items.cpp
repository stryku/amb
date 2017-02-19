#include "db/Items.hpp"
#include "db/static/items/ItemsDbData.hpp"
#include "log/log.hpp"

#include <QDebug>

namespace Amb
{
    namespace Db
    {
        Items::Items()
        {
            for (size_t i = 0; i < Static::Items::ItemsDb.size(); ++i)
            {
                map[Static::Items::ItemsDb[i].name] = i;

                for (size_t j = 0; j < Static::Items::ItemsDb[i].hashes.size(); ++j)
                {
                    const auto hash = Static::Items::ItemsDb[i].hashes[j];
                    hashMap[hash] = i;
                }
            }
        }

        Static::Items::Item Items::get(size_t id) const
        {
            if (id == BadId || id >= Static::Items::ItemsDb.size())
                return{};

            return Static::Items::ItemsDb[id];
        }

        Static::Items::Item Items::get(const std::string &name) const
        {
            const auto it = map.find(name);

            if (it == std::end(map))
                return{};

            const auto id = it->second;
            return Static::Items::ItemsDb[id];
        }

        ItemId Items::getId(const std::string &name) const
        {
            const auto it = map.find(name);

            if (it == std::end(map))
                return static_cast<ItemId>(-1);

            const auto id = it->second;
            return id;
        }

        std::vector<std::string> Items::getNames() const
        {
            std::vector<std::string> ret;

            for (const auto &item : Static::Items::ItemsDb)
                ret.emplace_back(item.name);

            return ret;
        }

        size_t Items::getIdByHash(const cexpr::hash_t &hash) const
        {
            const auto it = hashMap.find(hash);

            if (it == std::end(hashMap))
                return BadId;

            const auto id = it->second;
            return id;
        }

        bool Items::isThisEmpty(size_t id) const
        {
            const cexpr::hash_t emptyHash{ 11876655800301230214 };

            return Static::Items::ItemsDb[id].hashes[0] == emptyHash;
        }

        ItemId Items::getByName(const std::string &name) const
        {
            const auto found = map.find(name);

            if (found == std::cend(map))
            {
                LOG_DEBUG("Item %s not found", name.c_str());
                return BadId;
            }
            else
                return found->second;
        }
    }
}

