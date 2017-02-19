#include "log/condition/ImageLogUniqueCondition.hpp"
#include "graphics/Image.hpp"

#include <algorithm>

namespace Amb
{
    namespace Log
    {
        namespace Condition
        {
            bool ImageLogUniqueCondition::shouldLogDerived(const Graphics::Image& img) const
            {
                return std::find(std::cbegin(alreadyLoggerImagesHashes),
                                 std::cend(alreadyLoggerImagesHashes),
                                 img.hash()) == std::cend(alreadyLoggerImagesHashes);
            }

            void ImageLogUniqueCondition::willLogThis(const Graphics::Image& img)
            {
                alreadyLoggerImagesHashes.push_back(img.hash());
            }
        }
    }
}
