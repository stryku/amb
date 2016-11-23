#pragma once

#include "utils/Structs.hpp"


namespace Amb
{
    namespace Graphics
    {
        class Image;
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
            {}

            size_t captureId(const Pos &pos) const;

        private:
            const Graphics::Image &screen;
            const Db::Items &itemsDb;
        };
    }
}
