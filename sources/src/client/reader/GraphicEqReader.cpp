#include "client/reader/GraphicEqReader.hpp"
#include "utils/Structs.hpp"
#include "log/log.hpp"
#include "graphics/Image.hpp"

namespace
{
    constexpr Amb::Offset kAmuletOffset{ 1, 15 };
    constexpr Amb::Offset kHelmetOffset{ 31, 1 };
    constexpr Amb::Offset kBackpackOffset{ 73, 15 };
    constexpr Amb::Offset kWeaponOffset{ 1, 51 };
    constexpr Amb::Offset kShieldOffset{ 73, 51 };
    constexpr Amb::Offset kArmorOffset{ 37, 37 };
    constexpr Amb::Offset kLegsOffset{ 37, 73 };
    constexpr Amb::Offset kBootsOffset{ 37, 109 };
    constexpr Amb::Offset kAmunitionOffset{ 73, 87 };
    constexpr Amb::Offset kRingOffset{ 1, 87 };
}

namespace Amb
{
    namespace Client
    {
        namespace Reader
        {
            GraphicEqReader::GraphicEqReader(const Graphics::Image& screen)
                : screen{ screen }
            {}

            boost::optional<EqItems> GraphicEqReader::read()
            {
                const auto posOptional = eqFinder.find();

                if (!posOptional)
                {
                    LOG_DEBUG("GraphicEqReader::read couldn't find eq");
                    return {};
                }

                const auto pos = *posOptional;

                EqItems eq;

                eq.amulet = readItem(pos, kAmuletOffset);
                eq.amunition.id = readItem(pos, kAmunitionOffset);
                eq.armor = readItem(pos, kArmorOffset);
                eq.backpack = readItem(pos, kBackpackOffset);
                eq.boots = readItem(pos, kBootsOffset);
                eq.head = readItem(pos, kHelmetOffset);
                eq.legs = readItem(pos, kLegsOffset);
                eq.ring = readItem(pos, kRingOffset);
                eq.shield = readItem(pos, kShieldOffset);
                eq.weapon = readItem(pos, kWeaponOffset);

                return eq;
            }

            size_t GraphicEqReader::readItem(Offset eqPos, Offset offset) const
            {
                Rect rect{ 0, 0, 32, 21 };

                rect.setPos(Pos::from(eqPos + offset));

                const auto sprite = screen.getSprite(rect);
                const auto hash = sprite.hash();
                const auto id = items.getIdByHash(hash);

                return id;
            }
        }
    }
}
