#include "capture/ItemCapturer.hpp"
#include "graphics/Image.hpp"
#include "cexpr/crypto.hpp"
#include "db/Items.hpp"

namespace AMB
{
    namespace Capture
    {

        size_t ItemCapturer::captureId(const Pos &pos) const
        {
            const auto itemSprite = screen.getSprite(pos.x, pos.y, 32, 21);
            const auto hash = itemSprite.hash();

            return itemsDb.getIdByHash(hash);
        }
    }
}
