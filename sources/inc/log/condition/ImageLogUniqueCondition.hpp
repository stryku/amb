#pragma once

#include "log/condition/LoggerCondition.hpp"
#include "hash/Hash.hpp"

#include <vector>

namespace Amb
{
    namespace Graphics
    {
        struct Image;
    }

    namespace Log
    {
        namespace Condition
        {
            class ImageLogUniqueCondition : public LoggerCondition<ImageLogUniqueCondition, Graphics::Image>
            {
            public:
                bool shouldLogDerived(const Graphics::Image& img) const;
                void willLogThis(const Graphics::Image& img) override;

            private:
                std::vector<Hash::HashType> alreadyLoggerImagesHashes;
            };
        }
    }
}
