#include "log/condition/ImageLogOnceCondition.hpp"

namespace Amb
{
    namespace Log
    {
        namespace Condition
        {
            bool ImageLogOnceCondition::shouldLog(const cexpr::hash_t&)
            {
                return !alreadyLogged;
            }

            bool ImageLogOnceCondition::willLogThis(const cexpr::hash_t&)
            {
                alreadyLogged = true;
            }
        }
    }
}
