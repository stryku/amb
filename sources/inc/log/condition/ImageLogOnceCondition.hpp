#pragma once

#include "log/condition/ILoggerCondition.hpp"

#include <cexpr/crypto.hpp>

namespace Amb
{
    namespace Log
    {
        namespace Condition
        {
            class ImageLogOnceCondition : public ILoggerCondition<cexpr::hash_t>
            {
            public:
                bool shouldLog(const cexpr::hash_t&) override;
                bool willLogThis(const cexpr::hash_t&) override;

            private:
                bool alreadyLogged{ false };
            };
        }
    }
}
