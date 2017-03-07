#pragma once

#include "client/reader/IEqReader.hpp"
#include "client/finder/GraphicEqFinder.hpp"
#include "db/Items.hpp"

namespace Amb
{
    namespace Graphics
    {
        struct Image;
    }

    namespace Client
    {
        namespace Reader
        {
            class GraphicEqReader : public IEqReader
            {
            public:
                explicit GraphicEqReader(const Graphics::Image& screen);

                boost::optional<EqItems> read() override;

            private:
                size_t readItem(Offset eqPos, Offset offset) const;

                Finder::GraphicEqFinder eqFinder;
                const Graphics::Image& screen;
                const Db::Items items;
            };
        }
    }
}
