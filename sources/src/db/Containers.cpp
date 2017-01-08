#include "db/Containers.hpp"
#include "db/static/containers/ContainersDbData.hpp"

namespace Amb
{
    namespace Db
    {
        Containers::Containers()
        {
            for (size_t i = 0; i < Static::Containers::ContainersDb.size(); ++i)
            {
                nameToIdMap[Static::Containers::ContainersDb[i].name] = i;
                iconHashToId[Static::Containers::ContainersDb[i].iconHash] = i;
            }
        }

        Static::Containers::Item Containers::get(size_t id) const
        {
            if (id == BadId || id >= Static::Containers::ContainersDb.size())
                return{};

            return Static::Containers::ContainersDb[id];
        }

        Static::Containers::Item Containers::get(const std::string &name) const
        {
            const auto it = nameToIdMap.find(name);

            if (it == std::end(nameToIdMap))
                return{};

            const auto id = it->second;
            return Static::Containers::ContainersDb[id];
        }

        ItemId Containers::getId(const std::string &name) const
        {
            const auto it = nameToIdMap.find(name);

            if (it == std::end(nameToIdMap))
                return static_cast<ItemId>(-1);

            const auto id = it->second;
            return id;
        }

        std::vector<std::string> Containers::getNames() const
        {
            std::vector<std::string> ret;

            for (const auto &item : Static::Containers::ContainersDb)
                ret.emplace_back(item.name);

            return ret;
        }

        size_t Containers::getIdByHash(const cexpr::hash_t &hash) const
        {
            const auto it = iconHashToId.find(hash);

            if (it == std::end(iconHashToId))
                return BadId;

            const auto id = it->second;
            return id;
        }

        bool Containers::existByName(const std::string &name) const
        {
            return nameToIdMap.find(name) != std::cend(nameToIdMap);
        }
    }
}

