#include "log/condition/ImageLogOnceCondition.hpp"

namespace Amb
{
    namespace Log
    {
        namespace Condition
        {
            bool ImageLogOnceCondition::shouldLogDerived(const cexpr::hash_t&)
            {
                return !alreadyLogged;
            }

            void ImageLogOnceCondition::willLogThis(const cexpr::hash_t&)
            {
                alreadyLogged = true;
            }
        }
    }
}
