#include "capture/ItemCapturer.hpp"
#include "graphics/Image.hpp"
#include "cexpr/crypto.hpp"
#include "db/Items.hpp"

namespace Amb
{
    namespace Capture
    {

        size_t ItemCapturer::captureId(const Pos &pos) const
        {
            const auto itemSprite = screen.getSprite(pos.x, pos.y, 32, 21);
            itemSprite.toCb();
            const auto hash = itemSprite.hash();

            const auto id =  itemsDb.getIdByHash(hash);

            if (id == Db::Items::BadId)
                missingItemsLogger.log(itemSprite);

            return id;
        }

        void ItemCapturer::setEnableDebugLogs(bool enabled) const
        {
            missingItemsLogger.setExternalBool(enabled);
        }

    }
}
