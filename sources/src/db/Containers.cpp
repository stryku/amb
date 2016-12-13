#include "db/Containers.hpp"

namespace
{
    using Item = Amb::Db::Containers::Container;
    const std::array<Item, 43> ContainersDb = { Item{ "moon backpack", 7302774003641252317, 8286647595610441226 }, Item{ "jewelled backpack", 11805938743688557866, 2558967370518497139 }, Item{ "locker", 10080972675383643584, 502727070198827364 }, Item{ "depot chest", 14133617818832932406, 3282135638542259486 }, Item{ "chest", 15178257979108126671, 2933980120649212592 }, Item{ "crate", 9366275097875813515, 8351412186044677541 }, Item{ "brocade bag", 11850812404544627279, 12008344018712728376 }, Item{ "present", 5556955562225213699, 17429503272115382089 }, Item{ "red bag", 10980913921654133470, 2374642582951716838 }, Item{ "golden bag", 11937412524162278196, 15404215108185616077 }, Item{ "yellow bag", 3011300737743754618, 15132713055346194617 }, Item{ "blue bag", 995688424310781377, 12410635874077512943 }, Item{ "purple bag", 5800233003185374234, 3584877535502273646 }, Item{ "green bag", 6506650961814726445, 11285076817513672132 }, Item{ "christmas present", 17416954868543755400, 1355399053661769296 }, Item{ "bag", 13129470216875908453, 11481923709127035707 }, Item{ "orange bag", 16643680198803482429, 15521461516516945672 }, Item{ "buggy backpack", 15710371521103696762, 8044511437327817949 }, Item{ "shopping bag", 18403899485924506514, 542695138179191650 }, Item{ "backpack", 12340825804534595157, 11341583302554011318 }, Item{ "beach backpack", 7595014969669418224, 3491405041620190556 }, Item{ "blue backpack", 8401189691833503033, 16133603308860517742 }, Item{ "brocade backpack", 2848923290313739790, 9614925588228373949 }, Item{ "camofluage backpack", 3246170784934337396, 10182510019765076341 }, Item{ "demon backpack", 2198102403041114245, 17642531678253760581 }, Item{ "dragon backpack", 7505986074608054823, 5320258984221058545 }, Item{ "expedition backpack", 10578358947351453920, 2984444367152650356 }, Item{ "fur backpack", 1349239961482146649, 11074134725341158263 }, Item{ "fur bag", 14256398811940120193, 1718867862701827249 }, Item{ "glooth backpack", 8240123021701831197, 6728226554966437366 }, Item{ "green backpack", 17606301992713929722, 14339084036117341583 }, Item{ "grey backpack", 10680140779301808423, 12346474222218047059 }, Item{ "minotaur backpack", 12906995311838145904, 12033141576110277070 }, Item{ "orange backpack", 1303574690448924600, 1809877410058914046 }, Item{ "pirate backpack", 10688438427521591060, 16356831505560122047 }, Item{ "pirate bag", 4418954938001516549, 13302840486945258228 }, Item{ "purple backpack", 7210920891440306377, 7189649967171338999 }, Item{ "yellow backpack", 866280058167653219, 10107169850365426299 }, Item{ "red backpack", 14298510415070247460, 5752351085126681464 }, Item{ "golden backpack", 7114359056722398802, 5354088090883109055 }, Item{ "stamped parcel", 7100683172171048651, 1312810146198809731 }, Item{ "zaoan chess box", 8563196674510131989, 14470575250718724954 }, Item{ "anniversary backpack", 6277518085243983503, 797123853757932139 } };
}

namespace Amb
{
    namespace Db
    {
        Containers::Containers()
        {
            for (size_t i = 0; i < ContainersDb.size(); ++i)
            {
                nameToIdMap[ContainersDb[i].name] = i;
                iconHashToId[ContainersDb[i].iconHash] = i;
            }
        }

        Containers::Container Containers::get(size_t id) const
        {
            if (id == BadId || id >= ContainersDb.size())
                return{};

            return ContainersDb[id];
        }

        Containers::Container Containers::get(const std::string &name) const
        {
            const auto it = nameToIdMap.find(name);

            if (it == std::end(nameToIdMap))
                return{};

            const auto id = it->second;
            return ContainersDb[id];
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

            for (const auto &item : ContainersDb)
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
    }
}

