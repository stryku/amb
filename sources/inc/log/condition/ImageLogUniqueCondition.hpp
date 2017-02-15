#pragma once

#include "log/condition/LoggerCondition.hpp"

#include <cexpr/crypto.hpp>

#include <vector>

namespace Amb
{
    namespace Log
    {
        namespace Condition
        {
            class ImageLogUniqueCondition : public LoggerCondition<ImageLogUniqueCondition, cexpr::hash_t>
            {
            public:
                bool shouldLogDerived(const cexpr::hash_t& hash) const;
                void willLogThis(const cexpr::hash_t& hash) override;

            private:
                std::vector<cexpr::hash_t> alreadyLoggerImagesHashes;
            };
        }
    }
}
