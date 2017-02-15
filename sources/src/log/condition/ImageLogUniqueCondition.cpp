#include "log/condition/ImageLogUniqueCondition.hpp"

#include <algorithm>

namespace Amb
{
    namespace Log
    {
        namespace Condition
        {
            bool ImageLogUniqueCondition::shouldLogDerived(const cexpr::hash_t& hash) const
            {
                return std::find(std::cbegin(alreadyLoggerImagesHashes),
                                 std::cend(alreadyLoggerImagesHashes),
                                 hash) == std::cend(alreadyLoggerImagesHashes);
            }

            void ImageLogUniqueCondition::willLogThis(const cexpr::hash_t& hash)
            {
                alreadyLoggerImagesHashes.push_back(hash);
            }
        }
    }
}
