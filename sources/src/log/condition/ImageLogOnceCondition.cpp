#include "log/condition/ImageLogOnceCondition.hpp"

namespace Amb
{
    namespace Log
    {
        namespace Condition
        {
            bool ImageLogOnceCondition::shouldLogDerived(const Graphics::Image&) const
            {
                return !alreadyLogged;
            }

            void ImageLogOnceCondition::willLogThis(const Graphics::Image&)
            {
                alreadyLogged = true;
            }
        }
    }
}
