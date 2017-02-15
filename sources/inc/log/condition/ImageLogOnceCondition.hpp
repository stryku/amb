#pragma once

#include "log/condition/LoggerCondition.hpp"

#include <cexpr/crypto.hpp>

namespace Amb
{
    namespace Log
    {
        namespace Condition
        {
            class ImageLogOnceCondition : public LoggerCondition<ImageLogOnceCondition, cexpr::hash_t>
            {
            public:
                bool shouldLogDerived(const cexpr::hash_t&) const;
                void willLogThis(const cexpr::hash_t&) override;

            private:
                bool alreadyLogged{ false };
            };
        }
    }
}
