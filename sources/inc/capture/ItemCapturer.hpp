#pragma once

#include "utils/Structs.hpp"
#include "log/ImageConditionalLogger.hpp"
#include "log/condition/ImageLogUniqueCondition.hpp"

namespace Amb
{
    namespace Graphics
    {
        struct Image;
    }

    namespace Db
    {
        class Items;
    }

    namespace Capture
    {
        class ItemCapturer
        {
        public:
            ItemCapturer(const Graphics::Image &screen,
                         const Db::Items &itemsDb)
                : screen{ screen }
                , itemsDb{ itemsDb }
                , missingItemsLogger{ "missing_items_logger", "logs/missing_items.txt" }
            {}

            size_t captureId(const Pos &pos) const;
            void setEnableDebugLogs(bool enabled) const;

        private:
            using UniqueImageLogger = Log::ImageConditionalLogger<Log::Condition::ImageLogUniqueCondition>;

            const Graphics::Image &screen;
            const Db::Items &itemsDb;
            mutable UniqueImageLogger missingItemsLogger;
        };
    }
}
